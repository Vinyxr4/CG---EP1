
OPT = ""
COMP = g++
COMPOBJ = $(COMP) -c $<

mesh: mesh.o
	g++ $^ -o $@

mesh.o: mesh.cpp
	$(COMPOBJ)

run:
	./mesh

clear:
	rm *.o

del_exec:
	rm mesh
