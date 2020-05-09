#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>

#include "text_bin.h"

// input queues
int lx_in1[2], lx_in2[2];
int hex1[2], hex2[2];

// output queue
int lx_out[2];

void xor_queues(int fd1, int fd2, int outfd) {
  ssize_t read_bytes = 0;
  ssize_t written_bytes = 0;
  unsigned char byte1, byte2, output;
  while (true) {
    read_bytes = read(fd1, &byte1, (size_t) 1);
    if (read_bytes < 0) {
      perror("");
      exit(errno);
    } else if (read_bytes == 0) {
      return;
    }
    read_bytes = read(fd2, &byte2, (size_t) 1);
    if (read_bytes < 0) {
      perror("");
      exit(errno);
    } else if (read_bytes == 0) {
      return;
    }
    output = byte1 ^ byte2;
    written_bytes = write(outfd, &output, 1);
    if (written_bytes < 0) {
      perror("");
      exit(errno);
    }
  }
}

void arg_into_queue(char arg[], size_t arg_size, int fd) {
  ssize_t written_chars = 0;
  written_chars = write(fd, arg, arg_size);
  if (written_chars < 0) {
    perror("");
    exit(errno);
  }
}

int main (int argc, char * argv[]) {
  if (argc <= 2) {
    fprintf(stderr, "%s needs two hex string as parameters\n", argv[0]);
    return 1;
  }
  //open pipes
  pipe(lx_in1);
  pipe(lx_in2);
  pipe(hex1);
  pipe(hex2);
  pipe(lx_out);
  arg_into_queue(argv[1], strlen(argv[1]), hex1[1]);
  arg_into_queue(argv[2], strlen(argv[2]), hex2[1]);
  close(hex1[1]);
  close(hex2[1]);
  hex_to_raw(hex1[0], lx_in1[1]);
  hex_to_raw(hex2[0], lx_in2[1]);
  close(hex1[0]);
  close(hex2[0]);
  close(lx_in1[1]);
  close(lx_in1[1]);
  xor_queues(lx_in1[0], lx_in2[0], lx_out[1]);
  close(lx_out[1]);
  raw_to_hex(lx_out[0], 1);
  close(lx_out[0]);
  printf("\n"); // just for pretty printing
  return 0;
}
