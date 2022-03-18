
CMP = gcc
FUNC = crossfunc
MAIN = crossmain
EXEC = runcross

$(EXEC): $(FUNC).o $(MAIN).o
	$(CMP) -g $(FUNC).o $(MAIN).o -o $(EXEC)

$(FUNC).o: $(FUNC).c $(FUNC).h
	$(CMP) -c $(FUNC).c -o $(FUNC).o

$(MAIN).o: $(MAIN).c $(FUNC).h
	$(CMP) -c $(MAIN).c -o $(MAIN).o

clean:
	rm *.o
	rm $(EXEC)

