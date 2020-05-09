// Check if a character is ASCII and printable
_Bool is_ascii(char chrin);

// Check if a string is made only of ASCII chars
_Bool is_str_ascii(char *strin);

// Return an array of char frequency
void char_freq(char *strin, int *freqs);

// Return a score based of char frequency
int char_freq_score(int *freqs);
