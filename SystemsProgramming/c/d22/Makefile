all:	liblibdinos.so d22

liblibdinos.so:	libdinos.c
	gcc -fPIC -shared -o liblibdinos.so libdinos.c

d22:	d22.c
	gcc -o d22 d22.c -llibdinos -L.

clean:
	rm -f liblibdinos.so
	rm -f d22
