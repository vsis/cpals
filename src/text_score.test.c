#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "text_score.h"

int test_non_ascii_chars() {
  int errors = 0;
  printf ("running: test_non_ascii_chars()()\n");
  if (is_ascii(0)) errors++;
  if (is_ascii(127)) errors++;
  if (is_ascii(1)) errors++;
  if (is_ascii(31)) errors++;
  if (is_ascii(10)) errors++;
  if (is_ascii(128)) errors++;
  if (is_ascii(192)) errors++;
  if (is_ascii(255)) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_non_ascii_chars() failed\n");
  }
  return errors;
}

int test_ascii_chars() {
  int errors = 0;
  printf ("running: test_ascii_chars()\n");
  if (! is_ascii(' ')) errors++;
  if (! is_ascii('~')) errors++;
  if (! is_ascii('A')) errors++;
  if (! is_ascii('a')) errors++;
  if (! is_ascii('}')) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_ascii_chars() failed\n");
  }
  return errors;
}

int test_non_ascii_string() {
  int errors = 0;
  char non_ascii1[5] = {0x01, 0x02, 0x03, 0x04, 0x00};
  char non_ascii2[5] = {'H', 'E', 'Y', 0x04, 0x00};
  printf ("running: test_non_ascii_string()\n");
  if (is_str_ascii(non_ascii1)) errors++;
  if (is_str_ascii(non_ascii2)) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_non_ascii_string() failed\n");
  }
  return errors;
}

int test_ascii_string() {
  int errors = 0;
  char ascii1[6] = "HELLO";
  char ascii2[6] = "BYE! ";
  char ascii3[6] = "";
  printf ("running: test_ascii_string()\n");
  if (! is_str_ascii(ascii1)) errors++;
  if (! is_str_ascii(ascii2)) errors++;
  if (! is_str_ascii(ascii3)) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_ascii_string() failed\n");
  }
  return errors;
}

int test_char_freq() {
  int errors = 0;
  int freqs1[256] = {0};
  int freqs2[256] = {0};
  int freqs3[256] = {0};
  char text1[20] = "HELLO WORLD!";
  char text2[6] = "aaaaa";
  char text3[1] = "";
  printf ("running: test_char_freq()\n");
  char_freq(text1, freqs1);
  char_freq(text2, freqs2);
  char_freq(text3, freqs3);
  if (freqs1[(int)'H'] != 1) errors++;
  if (freqs1[(int)'E'] != 1) errors++;
  if (freqs1[(int)'L'] != 3) errors++;
  if (freqs1[(int)'O'] != 2) errors++;
  if (freqs1[(int)' '] != 1) errors++;
  if (freqs1[(int)'R'] != 1) errors++;
  if (freqs1[(int)'D'] != 1) errors++;
  if (freqs1[(int)'!'] != 1) errors++;
  if (freqs2[(int)'a'] != 5) errors++;
  if (freqs2[(int)'b'] != 0) errors++;
  if (freqs2[(int)'c'] != 0) errors++;
  if (freqs3[(int)'A'] != 0) errors++;
  if (freqs3[(int)'B'] != 0) errors++;
  if (freqs3[(int)'C'] != 0) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_char_freq() failed\n");
  }
  return errors;
}

int test_char_freq_score() {
  int errors = 0;
  char text1[1] = "";
  char text2[20] = "HELLO WORLD!";
  int freqs1[256] = {0};
  int freqs2[256] = {0};
  printf ("running: test_char_freq_score()\n");
  char_freq(text1, freqs1);
  char_freq(text2, freqs2);
  if (char_freq_score(freqs1) != 0) errors++;
  if (char_freq_score(freqs2) != 1) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_char_freq_score() failed\n");
  }
  return errors;
}

int main (int argc, char * argv[]) {
  int errors = 0;
  errors += test_non_ascii_chars();
  errors += test_ascii_chars();
  errors += test_non_ascii_string();
  errors += test_ascii_string();
  errors += test_char_freq();
  errors += test_char_freq_score();
   if (errors == 0) {
    printf("All tests OK\n");
  } else {
    printf("Bruh, %d tests failed\n", errors);
  }
  return errors;
}
