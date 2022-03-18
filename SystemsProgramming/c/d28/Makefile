all:	liblibdinos.so d28 d28_asker d28_asker_fork

liblibdinos.so:	libdinos.c
	gcc -g -fPIC -shared -o libdinos.so libdinos.c

d28:	d28.c
	gcc -g -o d28 d28.c -ldinos -L.

d28_asker:	d28_asker.c
	gcc -o d28_asker d28_asker.c -lm

d28_asker_fork:	d28_asker_fork.c
	gcc -o d28_asker_fork d28_asker_fork.c	-lm

clean:
	rm -f libdinos.so
	rm -f d28
	rm -f d28_asker
	rm -f d28_asker_fork
