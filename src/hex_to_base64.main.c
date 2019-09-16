#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>

#include "text_bin.h"

#define HTB64_BUFFER_SIZE 512

// a pipe to store raw bytes
int bytes_pipe[2] = {0};

// read hex chars from stdin
// transform them to raw bytes
// and send those bytes to a pipe
void hex_to_raw() {
  char buffer[HTB64_BUFFER_SIZE] = {0};
  unsigned char bytes[HTB64_BUFFER_SIZE] = {0};
  int read_chars = 0;
  int written_bytes = 0;
  int half_buffer = 0;
  close(bytes_pipe[0]); //close unnused read end
  while (true) {
    read_chars = read(0, buffer, HTB64_BUFFER_SIZE);
    if (read_chars < 0) {
      perror("");
      exit(errno);
    }
    if (read_chars == 0) {
      close(bytes_pipe[1]);
      return;
    }
    half_buffer = read_chars / 2; // number of raw bytes are the half of hex chars
    hex_to_bytes(buffer, bytes, half_buffer);
    written_bytes = write (bytes_pipe[1], bytes, half_buffer);
    if (written_bytes < 0) {
      perror("");
      exit(errno);
    }
  }
}

// read raw bytes from pipe
// transform them to base64
// and send them to stdout
void raw_to_base64() {
  close(bytes_pipe[1]);
  bytes_to_base64(bytes_pipe[0], 1);
  close(bytes_pipe[0]);  
  printf("\n");
}

int main(int argc, char * argv[]) {
  int pid;
  pipe(bytes_pipe);
  pid = fork();
  if (pid < 0) {
    perror("");
    exit(errno);
  } else if (pid == 0) {
    hex_to_raw();
  } else {
    wait(NULL);
    raw_to_base64();
  }
  return 0;
}
