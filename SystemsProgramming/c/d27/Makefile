all:	liblibdinos.so liblibgeodist.so d27

liblibdinos.so:	libdinos.c
	gcc -g -fPIC -shared -o libdinos.so libdinos.c

liblibgeodist.so: libgeodist.c
	gcc -g -fPIC -shared -o libgeodist.so libgeodist.c

d27:	d27.c
	gcc -g -o d27 d27.c -ldinos -lgeodist -lm -L.

clean:
	rm -f libdinos.so
	rm -f libgeodist.so
	rm -f d27
