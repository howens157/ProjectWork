all:	liblibdinos.so liblibgeodist.so d25

liblibdinos.so:	libdinos.c
	gcc -g -fPIC -shared -o libdinos.so libdinos.c

liblibgeodist.so: libgeodist.c
	gcc -g -fPIC -shared -o libgeodist.so libgeodist.c

d25:	d25.c
	gcc -g -o d25 d25.c -ldinos -lgeodist -lm -L.

clean:
	rm -f libdinos.so
	rm -f libgeodist.so
	rm -f d25
