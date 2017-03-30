
OPT = ""
COMP = g++
COMPOBJ = $(COMP) -c $<

ep1: ep1.o
	g++ $^ -o $@

ep1.o: ep1.cpp
	$(COMPOBJ)

run:
	./ep1

clear:
	rm *.o

del_exec:
	rm ep1
