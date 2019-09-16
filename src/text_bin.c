#include <stdlib.h>
#include <stdio.h>

#include "text_bin.h"

// transforms two hexadecimal chars to a byte
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
      fprintf(stderr, "hex_to_bytes(): max_bytes: %d has been reached\n", max_bytes);
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

// given a byte and a rest, returns a base46 char and the new rest
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

// given 3 bytes returns 4 to 6 base64 chars.
// the number of base64 chars depends on number of trailing zeroes
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
char * bytes_to_base64(unsigned char * bytes) {
  return 0x0;
}