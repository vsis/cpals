#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "text_bin.h"

// transforms one hexadecimal char to a byte
unsigned char single_hex_to_byte(char a) {
  if ((a <= '9') && (a >= '0')) {
    return a - '0';
  } else if ((a >= 'A') && (a <= 'F')) {
    return a - 'A' + 10;
  } else if ((a >= 'a') && (a <= 'f')) {
    return a - 'a' + 10;
  } else {
    fprintf(stderr, "single_hex_to_byte(): %c is not an HEX\n", a);
    return 16;
  }
}

// transforms a string of hexadecimals to a byte array
void hex_to_bytes(char * hexs, unsigned char * bytes, int max_bytes) {
  char * current_hex = hexs;
  unsigned char * current_byte = bytes;
  unsigned char aux_bytes[2];
  int current_bytes = 0;
  while (*current_hex != 0x00) {
    // check if max_bytes has been reached. if so, GTFO
    if (current_bytes >= max_bytes) {
      return;
    }

    // read first hex
    aux_bytes[0] = single_hex_to_byte(*current_hex);
    current_hex++;

    // if next hex is NULL, there is a half byte
    if (*current_hex == 0x00) {
      fprintf(stderr, "hex_to_bytes(): incomplete byte\n");
      return;
    }
    // read second hex
    aux_bytes[1] = single_hex_to_byte(*current_hex);

    // we got both hexes, now get the byte
    *current_byte = (aux_bytes[0] << 4) | aux_bytes[1];

    // move all counters
    current_byte++;
    current_hex++;
    current_bytes++;
  }
}

// given a byte, returns a base46 char
char byte_to_base64(unsigned char byte) {
  unsigned char six_bytes = byte >> 2;
  //turn into a base64 ASCII char
  if (six_bytes < 26) {
    six_bytes += 'A';
  } else if (six_bytes < 52) {
    six_bytes += 'a' - 26;
  } else if (six_bytes < 62) {
    six_bytes += '0' - 52;
  } else if (six_bytes == 62) {
    six_bytes = '+';
  } else if (six_bytes == 63) {
    six_bytes = '/';
  } else {
    fprintf(stderr, "byte_to_base64(): 'six_bytes' is too big: %d\n", six_bytes);
    return '-';
  }
  return six_bytes;
}

// given 3 bytes and the number of trailing zeroes, returns 4 base64 chars
//  trailing zeroes are the number of 0x00 at the end of bytes that shouldn't be counted
void three_bytes_to_base64(unsigned char * bytes, char * base64, unsigned char trailing_zeroes ) {
  unsigned char aux;
  base64[0] = byte_to_base64(bytes[0]);
  aux = ((bytes[0] & 0x03) << 6) | (bytes[1] >> 2);
  base64[1] = byte_to_base64(aux);
  aux = ((bytes[1] & 0x0F) << 4) | (bytes[2] >> 4);
  base64[2] = byte_to_base64(aux);
  aux = bytes[2] << 2;
  base64[3] = byte_to_base64(aux);
  base64[4] = 0x00;
  switch(trailing_zeroes) {
    case 2:
      base64[2] = '=';
    case 1:
      base64[3] = '=';
  }
}

// transforms a bytes array to a base64 string
//  its parameters are: input file descriptor, with raw bytes,
//  and output file descriptor, with base64 chars
void bytes_to_base64(int infd, int outfd) {
  int written_chars, read_chars, trailing_zeroes;
  unsigned char raw_bytes[3];
  char base64[5];
  while (true) {
    read_chars = read(infd, raw_bytes, 3);
    if (read_chars < 0) {
      perror("");
      return;
    }
    trailing_zeroes = 3 - read_chars;
    switch (trailing_zeroes) {
      case 3:
        return;
      case 2:
        raw_bytes[1] = 0x00;
      case 1:
        raw_bytes[2] = 0x00;
    }
    three_bytes_to_base64(raw_bytes, base64, trailing_zeroes);
    written_chars = write(outfd, base64, 4);
    if (written_chars < 0) {
      perror("");
      return;
    }
  }
}
