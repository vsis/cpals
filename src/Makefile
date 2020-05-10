CC=gcc
BIN_TOOLS:= hex_to_base64 lets_xor single_byte_cracker

.SECONDARY:

all: $(BIN_TOOLS)

%.test: %.o %.test.c
	$(CC) $(CFLAGS) -g $*.o $@.c -o $@

# set 1 - challenge 1
hex_to_base64: text_bin.o hex_to_base64.main.c
	$(CC) $(CFLAGS) text_bin.o hex_to_base64.main.c -o $@

set1_challenge1: hex_to_base64
	echo "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" | ./hex_to_base64

# set 1 - challenge 2
lets_xor: text_bin.o lets_xor.main.c
	$(CC) $(CFLAGS) text_bin.o lets_xor.main.c -o $@

set1_challenge2: lets_xor
	./lets_xor "1c0111001f010100061a024b53535009181c" "686974207468652062756c6c277320657965"

# set 1 - challenge 3
single_byte_cracker: text_bin.o text_score.o single_byte_cracker.main.c
	$(CC) $(CFLAGS) text_bin.o text_score.o single_byte_cracker.main.c -o $@

set1_challenge3: single_byte_cracker
	./single_byte_cracker "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

set1_challenge4: single_byte_cracker
	./search_single_byte_cipher.sh input/4.txt

clean:
	rm -rf *.o *.test $(BIN_TOOLS)

.PHONY: clean set1_challenge1 set1_challenge2
