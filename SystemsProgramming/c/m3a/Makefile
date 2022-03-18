all:	simg_display simg_convert simg_edit

simg_edit:	simg_edit.c
	gcc -g -o simg_edit simg_edit.c -lsimg -L.

simg_convert:	simg_convert.c
	gcc -g -o simg_convert simg_convert.c -lsimg -L.

simg_display:	simg_display.c
	gcc -g -o simg_display simg_display.c -lsimg -L.

clean:
	rm -f simg_display
	rm -f simg_convert
	rm -f simg_edit
