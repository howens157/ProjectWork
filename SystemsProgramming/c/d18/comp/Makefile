all:	libfoo.so wrk

libfoo.so:	foo.c
	gcc -fPIC -shared -o libfoo.so foo.c

wrk:	wrk.c
	gcc -o wrk wrk.c -lfoo -L.

clean:
	rm -f wrk
	rm -f libfoo.so

