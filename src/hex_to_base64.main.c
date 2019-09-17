#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>

#include "text_bin.h"


// a pipe to store raw bytes
int bytes_pipe[2] = {0};

// read hex chars from stdin
// transform them to raw bytes
// and send those bytes to a pipe
void stdin_hex_to_raw() {
  close(bytes_pipe[0]); // close unnused read end of pipe
  hex_to_raw(0, bytes_pipe[1]);
  close(bytes_pipe[1]); // we are done writing to bytes pipe
}

// read raw bytes from pipe
// transform them to base64
// and send them to stdout
void raw_to_base64() {
  close(bytes_pipe[1]); // close unnused write end of pipe
  bytes_to_base64(bytes_pipe[0], 1);
  close(bytes_pipe[0]); // we are done reading from pipe, so close read end
  printf("\n"); // for the sake of pretty-printing
}

int main(int argc, char * argv[]) {
  int pid;
  pipe(bytes_pipe);
  pid = fork();
  if (pid < 0) {
    perror("");
    exit(errno);
  } else if (pid == 0) {
    stdin_hex_to_raw();
  } else {
    raw_to_base64();
    wait(NULL); // we are done processing, wait for children to exit
  }
  return 0;
}
