# Makefile for lab 9
#   "make" or "make all : creates all three executables
#   "make symbol" : creates the symbol executable
#   (similar for "make bounce" and "make funanim")
 
all: symbol bounce funanim

symbol: symbol.c 
	gcc symbol.c gfx.o -lX11 -lm -o symbol

bounce: bounce.c 
	gcc bounce.c gfx.o -lX11 -o bounce

funanim: funanim.c 
	gcc funanim.c gfx.o -lX11 -lm -o funanim

clean:
	rm symbol bounce funanim

