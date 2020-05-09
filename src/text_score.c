#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "text_score.h"

// Check if a character is ASCII and printable
_Bool is_ascii(char chrin) {
  return ((chrin > (char)31) && (chrin < (char)127));
}

// Check if a string is made only of ASCII chars
_Bool is_str_ascii(char *strin) {
  char * current_char;
  if (strin != NULL) {
    current_char = strin;
    while (*current_char != '\0') {
      if (! is_ascii(*current_char)) {
        return false;
      }
      current_char++;
    }
    return true;
  } else {
    return false;
  }
}

// Return an array of char frequency
void char_freq(char *strin, int *freqs) {
  char * current_char;
  if (strin != NULL) {
    current_char = strin;
    while (*current_char != '\0') {
      freqs[(int) *current_char]++;
      current_char++;
    }
  }
}

// Return a score based of char frequency
int char_freq_score(int *freqs) {
  int max_freq = 0, min_freq = 0;
  int index;
  for (index = 0; index < 256; index++) {
    if (max_freq < freqs[index]) {
      max_freq = freqs[index];
    }
    if (min_freq > freqs[index]) {
      min_freq = freqs[index];
    }
  }
  return max_freq - min_freq;
}

