all:	liblittlelib.so d18

liblittlelib.so:	littlelib.c
	gcc -fPIC -shared -o liblittlelib.so littlelib.c

d18:	d18.c
	gcc -o d18 d18.c -llittlelib -L.

clean:
	rm -f liblittlelib.so
	rm -f d18
