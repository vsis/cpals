// transforms one hexadecimal char to a byte
unsigned char single_hex_to_byte(char a);

// transforms a string of hexadecimals to a byte array
void hex_to_bytes(char * hexs, unsigned char * bytes, int max_bytes);

// given a byte, returns a base46 char
char byte_to_base64(unsigned char byte);

// given 3 bytes and the number of trailing zeroes, returns 4 base64 chars
//  trailing zeroes are the number of 0x00 at the end of bytes that shouldn't be counted
void three_bytes_to_base64(unsigned char * bytes, char * base64, unsigned char trailing_zeroes );

// transforms a bytes array to a base64 string
//  its parameters are: input file descriptor, with raw bytes,
//  and output file descriptor, with base64 chars
void bytes_to_base64(int infd, int outfd);
