CC=gcc
BIN_TOOLS:= hex_to_base64

.SECONDARY:

all: $(BIN_TOOLS)

%.test: %.o %.test.c
	$(CC) $(CFLAGS) -g $*.o $@.c -o $@

# set 1 - challenge 1
hex_to_base64: text_bin.o hex_to_base64.main.c
	$(CC) $(CFLAGS) text_bin.o hex_to_base64.main.c -o $@

set1_challenge1: hex_to_base64
	echo "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" | ./hex_to_base64

clean:
	rm -rf *.o *.test $(BIN_TOOLS)

.PHONY: clean set1_challenge1
