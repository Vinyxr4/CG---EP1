Students:                 | NUSP

Patrick Abrahão Menani    | 8941050
Vinícius Pessoa Duarte    | 8941043

For compiling the program just run the command "make" or "make mesh".
The code is in c++, so g++ compiler is necessary.

Makefile contains the following directives for testing:
	->make cylinder_test: Generates a .obj for a cylnder with n = 100.
	->make sphere_test:   Generates a .obj for a sphere with n = 100 and m = 100.
	->make torus_test:    Generates a .obj for a torus with n = 100, m = 100 and r = 0.25.

For running the mesh with custom values, run the program as indictaded on the PA specification section.

Our normals, except for the sphere, that is just the normalized vertex for it's the unit sphere, have
their partial derivatives already calculated and plugged into the calc functions.
