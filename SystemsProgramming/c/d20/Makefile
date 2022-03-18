all:	liblibdinos.so d20

liblibdinos.so:	libdinos.c
	gcc -fPIC -shared -o liblibdinos.so libdinos.c

d20:	d20.c
	gcc -o d20 d20.c -llibdinos -L.

clean:
	rm -f liblittlelib.so
	rm -f d20
