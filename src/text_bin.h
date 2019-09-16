// transforms two hexadecimal chars to a byte
unsigned char single_hex_to_byte(char a);

// transforms a string of hexadecimals to a byte array
void hex_to_bytes(char * hexs, unsigned char * bytes, int max_bytes);

// given a byte and a rest, returns a base46 char and the new rest
char byte_to_base64(unsigned char byte);

// given 3 bytes returns 4 to 6 base64 chars.
// the number of base64 chars depends on number of trailing zeroes
void three_bytes_to_base64(unsigned char * bytes, char * base64, unsigned char trailing_zeroes );

// transforms a bytes array to a base64 string
//  its parameters are: input file descriptor, with raw bytes,
//  and output file descriptor, with base64 chars
void bytes_to_base64(int infd, int outfd);
