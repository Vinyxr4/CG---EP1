
OPT = ""
COMP = g++
COMPOBJ = $(COMP) -c $<

mesh: mesh.o
	g++ $^ -o $@

mesh.o: mesh.cpp
	$(COMPOBJ)

cylinder_test:
	./mesh -n 100 cylinder cylinder_test.obj

sphere_test:
	./mesh -n 100 -m 100 sphere sphere_test.obj

clear:
	rm *.o
	rm mesh
