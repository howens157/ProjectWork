all:	liblibdinos.so liblibgeodist.so d24

liblibdinos.so:	libdinos.c
	gcc -g -fPIC -shared -o liblibdinos.so libdinos.c

liblibgeodist.so: libgeodist.c
	gcc -g -fPIC -shared -o liblibgeodist.so libgeodist.c

d24:	d24.c
	gcc -g -o d24 d24.c -llibdinos -llibgeodist -lm -L.

clean:
	rm -f liblibdinos.so
	rm -f liblibgeodist.so
	rm -f d24
