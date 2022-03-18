all:	liblibdinos.so liblibgeodist.so d23

liblibdinos.so:	libdinos.c
	gcc -fPIC -shared -o liblibdinos.so libdinos.c

liblibgeodist.so: libgeodist.c
	gcc -fPIC -shared -o liblibgeodist.so libgeodist.c

d23:	d23.c
	gcc -o d23 d23.c -llibdinos -llibgeodist -lm -L.

clean:
	rm -f liblibdinos.so
	rm -f liblibgeodist.so
	rm -f d23
