#Students:                 | NUSP

#Patrick Abrahão Menani    | 8941050
#Vinícius Pessoa Duarte    | 8941043

OBJ_DIR=objs/
OPT =-O2
COMP = g++ $(OPT)
COMPOBJ = $(COMP) -c $< -o $@
OBJS = $(patsubst %.o, objs/%.o, mesh.o Vertex.o global.o print.o calc.o)

mesh: $(OBJS)
	g++ $(OBJS) -o $@

$(OBJ_DIR)mesh.o: src/mesh.cpp lib/calc.h lib/Vertex.h lib/global.h lib/print.h
	$(COMPOBJ)

$(OBJ_DIR)Vertex.o: src/Vertex.cpp lib/Vertex.h lib/global.h
	$(COMPOBJ)

$(OBJ_DIR)global.o: src/global.cpp lib/global.h
	$(COMPOBJ)

$(OBJ_DIR)print.o: src/print.cpp lib/print.h lib/Vertex.h lib/global.h
	$(COMPOBJ)

$(OBJ_DIR)calc.o: src/calc.cpp lib/calc.h lib/Vertex.h lib/global.h
	$(COMPOBJ)

cylinder_test:
	./mesh -n 100 cylinder cylinder_test.obj

sphere_test:
	./mesh -n 100 -m 100 sphere sphere_test.obj

torus_test:
	./mesh -n 100 -m 100 -r 0.25 torus torus_test.obj

clear:
	rm $(OBJ_DIR)*.o
	rm mesh
