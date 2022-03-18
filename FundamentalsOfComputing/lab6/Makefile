oper: opermain.o operfn.o
	gcc opermain.o operfn.o -o oper

opermain.o: opermain.c operfn.h
	gcc -c opermain.c -o opermain.o

operfn.o: operfn.c operfn.h
	gcc -c operfn.c -o operfn.o

clean:
	rm oper
	rm *.o

