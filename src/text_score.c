#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "text_score.h"

// Check if a character is ASCII and printable
_Bool is_ascii(char chrin) {
  return (((chrin > (char)31) && (chrin < (char)127)) || (chrin == '\n'));
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
  unsigned char * current_char;
  if (strin != NULL) {
    current_char = (unsigned char *) strin;
    while (*current_char != (unsigned char) '\0') {
      freqs[(int) *current_char]++;
      current_char++;
    }
  }
}

// Return a score based of char frequency
int char_freq_score(int *freqs) {
  // We will use the most common letters in english, with a given factor
  // acording its expected frequency.
  // We also give a relativy high factor to space char
  int score = 0;
  score += 20 * freqs[(int) ' '];
  score += 13 * (freqs[(int) 'e'] + freqs[(int) 'E']);
  score += 10 * (freqs[(int) 't'] + freqs[(int) 'T']);
  score += 9 * (freqs[(int) 'a'] + freqs[(int) 'A']);
  score += 8 * (freqs[(int) 'o'] + freqs[(int) 'O']);
  score += 7 * (freqs[(int) 'i'] + freqs[(int) 'I']);
  score += 7 * (freqs[(int) 'n'] + freqs[(int) 'N']);
  score += 6 * (freqs[(int) 's'] + freqs[(int) 'S']);
  score += 6 * (freqs[(int) 'h'] + freqs[(int) 'H']);
  score += 6 * (freqs[(int) 'r'] + freqs[(int) 'R']);
  score += 4 * (freqs[(int) 'd'] + freqs[(int) 'D']);
  score += 4 * (freqs[(int) 'l'] + freqs[(int) 'L']);
  return score;
}

