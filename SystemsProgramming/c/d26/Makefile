all:	liblibdinos.so liblibgeodist.so d26

liblibdinos.so:	libdinos.c
	gcc -g -fPIC -shared -o libdinos.so libdinos.c

liblibgeodist.so: libgeodist.c
	gcc -g -fPIC -shared -o libgeodist.so libgeodist.c

d26:	d26.c
	gcc -g -o d26 d26.c -ldinos -lgeodist -lm -lpthread -L.

clean:
	rm -f libdinos.so
	rm -f libgeodist.so
	rm -f d26
