all:	libsoftmodem.so

libsoftmodem.so:	libsoftmodem.c
	gcc -g -fPIC -shared -o libsoftmodem.so libsoftmodem.c -lm

clean:
	rm -f libsoftmodem.so

