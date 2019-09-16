CC=gcc

.SECONDARY:

%.test: %.o %.test.c
	$(CC) $(CFLAGS) -g $*.o $@.c -o $@

clean:
	rm -rf *.o *.test

.PHONY: clean
