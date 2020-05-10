#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "text_bin.h"
#include "text_score.h"

// Max length of an input string
#define SBC_MAX_INPUT_SIZE 1024

void apply_xor(unsigned char key, ssize_t length, char * input_str, char * output_str) {
  int index = 0;
  for (index = 0; index < (int) length; index++) {
    output_str[index] = key ^ input_str[index];
  }
  output_str[length] = '\0';
}

void reset_freqs(int freqs[]) {
  int index;
  for (index = 0; index < 256; index++) {
    freqs[index] = 0;
  }
}

int main (int argc, char *argv[]) {
  //the possible key to decipher
  unsigned char current_key = 0;
  
  // We asume argv[1] is our intput data
  unsigned char cipher_text[SBC_MAX_INPUT_SIZE] = {0};
  hex_to_bytes(argv[1], cipher_text, SBC_MAX_INPUT_SIZE); 

  // Calculate the plain text size
  ssize_t plain_text_length = strlen(argv[1]) / 2;

  // Calculate a score for every key
  int freqs[256] = {0}, scores[256] = {0}, index;
  _Bool asciis[256];
  char plain_text[SBC_MAX_INPUT_SIZE];
  for (index = 0; index < 256; index++) {
    apply_xor((unsigned char) index, plain_text_length, cipher_text, plain_text);
    reset_freqs(freqs);
    char_freq(plain_text, freqs);
    scores[index] = char_freq_score(freqs);
    asciis[index] = is_str_ascii(plain_text);
  }

  // Get best score
  int best_score = 0, best_index = 0;
  for (index = 0; index < 256; index++) {
    if (best_score < scores[index]) {
       best_score = scores[index];
       best_index = index;
    }
  }

  // Check if best score is not 0x00 (no cipher)
  // or not all chars are printable
  if ((best_score == 0) || (! asciis[best_index])) {
    printf("Fail =(\n");
    exit(1);
  }

  // Print best score result
  apply_xor((unsigned char) best_index, plain_text_length, cipher_text, plain_text);
  printf("Selected key: %d\n", best_index);
  printf("Selected score: %d\n", best_score);
  printf("Plain text: %s\n", plain_text);
  exit(0);
}
