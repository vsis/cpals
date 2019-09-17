#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "text_bin.h"

int test_single_hex_to_byte() {
  int errors = 0;
  printf("running: test_single_hex_to_byte()\n");
  if (single_hex_to_byte('A') != 0xA) errors++;
  if (single_hex_to_byte('a') != 0xA) errors++;
  if (single_hex_to_byte('B') != 0xB) errors++;
  if (single_hex_to_byte('b') != 0xB) errors++;
  if (single_hex_to_byte('0') != 0x0) errors++;
  if (single_hex_to_byte('1') != 0x1) errors++;
  if (single_hex_to_byte('2') != 0x2) errors++;
  if (single_hex_to_byte('3') != 0x3) errors++;
  if (single_hex_to_byte('9') != 0x9) errors++;
  if (single_hex_to_byte('f') != 0xf) errors++;
  if (single_hex_to_byte('g') != 0x10) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_single_hex_to_byte() failed\n");
  }
  return errors;
}

int test_hex_to_bytes() {
  int errors = 0;
  char * test1 = "0001";
  char * test2 = "00FF";
  char * test3 = "00010203040506070809";
  char * test4 = "68656c6c6f20776f726c64";
  unsigned char res1[2], res2[2], res3[10], res4[11], small[1];
  printf("running: test_hex_to_bytes()\n");
  hex_to_bytes(test1, res1, 2);
  hex_to_bytes(test2, res2, 2);
  hex_to_bytes(test3, res3, 10);
  hex_to_bytes(test4, res4, 11);
  hex_to_bytes(test4, NULL, 0);
  hex_to_bytes(test4, small, 1);
  // let's check
  if (res1[0] != 0x00) errors++;
  if (res1[1] != 0x01) errors++;
  if (res2[0] != 0x00) errors++;
  if (res2[1] != 0xff) errors++;
  if (res3[0] != 0x00) errors++;
  if (res3[1] != 0x01) errors++;
  if (res3[2] != 0x02) errors++;
  if (res3[3] != 0x03) errors++;
  if (res3[4] != 0x04) errors++;
  if (res3[5] != 0x05) errors++;
  if (res3[6] != 0x06) errors++;
  if (res3[7] != 0x07) errors++;
  if (res3[8] != 0x08) errors++;
  if (res3[9] != 0x09) errors++;
  if (res4[0] != 0x68) errors++;
  if (res4[1] != 0x65) errors++;
  if (res4[2] != 0x6c) errors++;
  if (res4[3] != 0x6c) errors++;
  if (res4[4] != 0x6f) errors++;
  if (res4[5] != 0x20) errors++;
  if (res4[6] != 0x77) errors++;
  if (res4[7] != 0x6f) errors++;
  if (res4[8] != 0x72) errors++;
  if (res4[9] != 0x6c) errors++;
  if (res4[10] != 0x64) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_hex_to_bytes() failed\n");
  }
  return errors;
}

int test_byte_to_base64() {
  unsigned char test1 = 0x00;
  unsigned char test2 = 0x0F;
  unsigned char test3 = 0xFF;
  unsigned char test4 = 0x77;
  unsigned char test5 = 0xF0;
  unsigned char result1;
  unsigned char result2;
  unsigned char result3;
  unsigned char result4;
  unsigned char result5;
  int errors = 0;
  printf("running: test_byte_to_base64()\n");
  result1 = byte_to_base64(test1);
  result2 = byte_to_base64(test2);
  result3 = byte_to_base64(test3);
  result4 = byte_to_base64(test4);
  result5 = byte_to_base64(test5);
  if (result1 != 'A') errors++;
  if (result2 != 'D') errors++;
  if (result3 != '/') errors++;
  if (result4 != 'd') errors++;
  if (result5 != '8') errors++;
  if (errors != 0) {
    fprintf(stderr, "test_byte_to_base64() failed\n");
  }
  return errors;
}

int test_three_bytes_to_base64() {
  int errors = 0;
  unsigned char test1[3] = {0x00, 0x00, 0x00};
  unsigned char test2[3] = {0xff, 0xff, 0xff};
  unsigned char test2_1z[3] = {0xff, 0xff, 0x00};
  unsigned char test2_2z[3] = {0xff, 0x00, 0x00};
  unsigned char test3[3] = {0x49, 0x27, 0x6d};
  unsigned char test3_1z[3] = {0x49, 0x27, 0x00};
  unsigned char test3_2z[3] = {0x49, 0x00, 0x00};
  unsigned char test4[3] = {0x20, 0x6b, 0x69};
  unsigned char test4_1z[3] = {0x20, 0x6b, 0x00};
  unsigned char test4_2z[3] = {0x20, 0x00, 0x00};
  char res1[5];
  char res1_1z[5];
  char res1_2z[5];
  char res2[5];
  char res2_1z[5];
  char res2_2z[5];
  char res3[5];
  char res3_1z[5];
  char res3_2z[5];
  char res4[5];
  char res4_1z[5];
  char res4_2z[5];
  printf("running: test_three_bytes_to_base64()\n");
  three_bytes_to_base64(test1, res1, 0);
  three_bytes_to_base64(test1, res1_1z, 1);
  three_bytes_to_base64(test1, res1_2z, 2);
  three_bytes_to_base64(test2, res2, 0);
  three_bytes_to_base64(test2_1z, res2_1z, 1);
  three_bytes_to_base64(test2_2z, res2_2z, 2);
  three_bytes_to_base64(test3, res3, 0);
  three_bytes_to_base64(test3_1z, res3_1z, 1);
  three_bytes_to_base64(test3_2z, res3_2z, 2);
  three_bytes_to_base64(test4, res4, 0);
  three_bytes_to_base64(test4_1z, res4_1z, 1);
  three_bytes_to_base64(test4_2z, res4_2z, 2);
  if (strcmp(res1, "AAAA") != 0) errors++;
  if (strcmp(res1_1z, "AAA=") != 0) errors++;
  if (strcmp(res1_2z, "AA==") != 0) errors++;
  if (strcmp(res2, "////") != 0) errors++;
  if (strcmp(res2_1z, "//8=") != 0) errors++;
  if (strcmp(res2_2z, "/w==") != 0) errors++;
  if (strcmp(res3, "SSdt") != 0) errors++;
  if (strcmp(res3_1z, "SSc=") != 0) errors++;
  if (strcmp(res3_2z, "SQ==") != 0) errors++;
  if (strcmp(res4, "IGtp") != 0) errors++;
  if (strcmp(res4_1z, "IGs=") != 0) errors++;
  if (strcmp(res4_2z, "IA==") != 0) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_three_bytes_to_base64() failed\n");
  }
  return errors;
}

int test_bytes_to_base64() {
  int raw_bytes[2], base64[2], errors = 0;
  unsigned char test1[10] = {0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 0x69, 0x6e};
  unsigned char test2[6] = {0x67, 0x20, 0x79, 0x6f, 0x75, 0x72};
  char result1[20] = {0}, result2[20] = {0};
  printf("running: test_bytes_to_base64()\n");

  // firt test
  if ((pipe(raw_bytes) < 0) || (pipe(base64) < 0)) {
    perror("");
    return ++errors;
  }
  if (write(raw_bytes[1], test1, 10) < 0) {
    perror("");
    return ++errors;
  }
  close(raw_bytes[1]);
  bytes_to_base64(raw_bytes[0], base64[1]);
  close(base64[1]);
  close(raw_bytes[0]);
  if (read(base64[0], result1, 20) < 0) {
    perror("");
    return ++errors;
  }
  close(base64[0]);

  // second test
  if ((pipe(raw_bytes) < 0) || (pipe(base64) < 0)) {
    perror("");
    return ++errors;
  }
  if (write(raw_bytes[1], test2, 6) < 0) {
    perror("");
    return ++errors;
  }
  close(raw_bytes[1]);
  bytes_to_base64(raw_bytes[0], base64[1]);
  close(base64[1]);
  close(raw_bytes[0]);
  if (read(base64[0], result2, 20) < 0) {
    perror("");
    return ++errors;
  }
  close(base64[0]);

  // check results
  if (strcmp(result1, "SSdtIGtpbGxpbg==") != 0) errors++;
  if (strcmp(result2, "ZyB5b3Vy") != 0 ) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_bytes_to_base64() failed\n");
  }
  return errors;
}

int test_hex_to_raw() {
  int errors = 0;
  char * test = "68656c6c6f20776f726c64";
  unsigned char res[11];
  int hex_pipe[2], raw_pipe[2];
  printf("running: test_hex_to_raw()\n");
  pipe(hex_pipe);
  pipe(raw_pipe);
  if (write(hex_pipe[1], test, 22) < 0) {
    perror("");
    return ++errors;
  }
  close(hex_pipe[1]);
  hex_to_raw(hex_pipe[0], raw_pipe[1]);
  close(hex_pipe[0]);
  close(raw_pipe[1]);
  if (read(raw_pipe[0], res, 11) < 0) {
    perror("");
    return ++errors;
  }
  close(raw_pipe[0]);
  if (res[0] != 0x68) errors++;
  if (res[1] != 0x65) errors++;
  if (res[2] != 0x6c) errors++;
  if (res[3] != 0x6c) errors++;
  if (res[4] != 0x6f) errors++;
  if (res[5] != 0x20) errors++;
  if (res[6] != 0x77) errors++;
  if (res[7] != 0x6f) errors++;
  if (res[8] != 0x72) errors++;
  if (res[9] != 0x6c) errors++;
  if (res[10] != 0x64) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_hex_to_raw() failed\n");
  }
  return errors;
}

int test_byte_to_single_char() {
  int errors = 0;
  printf ("running: test_byte_to_single_char()\n");
  if (byte_to_single_char(0x00) != '0') errors++;
  if (byte_to_single_char(0x01) != '1') errors++;
  if (byte_to_single_char(0x02) != '2') errors++;
  if (byte_to_single_char(0x03) != '3') errors++;
  if (byte_to_single_char(0x04) != '4') errors++;
  if (byte_to_single_char(0x05) != '5') errors++;
  if (byte_to_single_char(0x06) != '6') errors++;
  if (byte_to_single_char(0x07) != '7') errors++;
  if (byte_to_single_char(0x08) != '8') errors++;
  if (byte_to_single_char(0x09) != '9') errors++;
  if (byte_to_single_char(0x0a) != 'A') errors++;
  if (byte_to_single_char(0x0b) != 'B') errors++;
  if (byte_to_single_char(0x0c) != 'C') errors++;
  if (byte_to_single_char(0x0d) != 'D') errors++;
  if (byte_to_single_char(0x0e) != 'E') errors++;
  if (byte_to_single_char(0x0f) != 'F') errors++;
  if (byte_to_single_char(0x10) != 0x00) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_byte_to_single_char() failed\n");
  }
  return errors;
}

int test_byte_to_hex() {
  int errors = 0;
  unsigned char test1 = 0x00;
  unsigned char test2 = 0x01;
  unsigned char test3 = 0x0F;
  unsigned char test4 = 0x23;
  unsigned char test5 = 0x45;
  unsigned char test6 = 0xFF;
  char res1[3] = {0};
  char res2[3] = {0};
  char res3[3] = {0};
  char res4[3] = {0};
  char res5[3] = {0};
  char res6[3] = {0};
  printf ("running: test_byte_to_hex()\n");
  byte_to_hex(test1, res1);
  byte_to_hex(test2, res2);
  byte_to_hex(test3, res3);
  byte_to_hex(test4, res4);
  byte_to_hex(test5, res5);
  byte_to_hex(test6, res6);
  if (strcmp(res1, "00") != 0) errors++;
  if (strcmp(res2, "01") != 0) errors++;
  if (strcmp(res3, "0F") != 0) errors++;
  if (strcmp(res4, "23") != 0) errors++;
  if (strcmp(res5, "45") != 0) errors++;
  if (strcmp(res6, "FF") != 0) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_byte_to_single_char() failed\n");
  }
  return errors;
}

int test_raw_to_hex() {
  int errors = 0;
  int raw_pipe[2], hex_pipe[2];
  int written_bytes = 0;
  int read_hex = 0;
  char hex[23] = {0};
  unsigned char test[11] = {0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64};
  printf ("running: test_raw_to_hex()\n");
  pipe(raw_pipe);
  pipe(hex_pipe);
  written_bytes = write(raw_pipe[1], test, 11);
  if (written_bytes < 0) {
    perror("");
    return ++errors;
  }
  close(raw_pipe[1]);
  raw_to_hex(raw_pipe[0], hex_pipe[1]);
  close(hex_pipe[1]);
  close(raw_pipe[0]);
  read_hex = read(hex_pipe[0], hex, 22);
  if (read_hex < 0) {
    perror("");
    return ++errors;
  }
  close(hex_pipe[0]);
  if (strcmp(hex, "68656C6C6F20776F726C64") != 0) errors++;
  if (errors != 0) {
    fprintf(stderr, "test_raw_to_hex() failed\n");
  }
  return errors;
}

int main (int argc, char * argv[]) {
  int errors = 0;
  errors += test_single_hex_to_byte();
  errors += test_hex_to_bytes();
  errors += test_byte_to_base64();
  errors += test_three_bytes_to_base64(); 
  errors += test_bytes_to_base64();
  errors += test_hex_to_raw();
  errors += test_byte_to_single_char();
  errors += test_byte_to_hex();
  errors += test_raw_to_hex();
  if (errors == 0) {
    printf("All tests OK\n");
  } else {
    printf("Bruh, %d tests failed\n", errors);
  }
  return errors;
}
