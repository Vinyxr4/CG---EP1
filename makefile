
OPT = ""
COMP = g++
COMPOBJ = $(COMP) -c $<

mesh: mesh.o Vertex.o global.o print.o calc.o
	g++ $^ -o $@
 
mesh.o: mesh.cpp lib/calc.h lib/Vertex.h lib/global.h lib/print.h
	$(COMPOBJ)

Vertex.o: Vertex.cpp lib/Vertex.h lib/global.h
	$(COMPOBJ)

global.o: global.cpp lib/global.h
	$(COMPOBJ)

print.o: print.cpp lib/print.h lib/Vertex.h lib/global.h
	$(COMPOBJ)

calc.o: calc.cpp lib/calc.h lib/Vertex.h lib/global.h
	$(COMPOBJ)

cylinder_test:
	./mesh -n 100 cylinder cylinder_test.obj

sphere_test:
	./mesh -n 100 -m 100 sphere sphere_test.obj

torus_test:
	./mesh -n 100 -m 100 -r 0.25 torus torus_test.obj

clear:
	rm objs/*.o
	rm mesh
