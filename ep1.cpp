#include <iostream>
#include <stdlib.h>
#include <vector>

void calculate_vertex (std::vector<float> vert, std::vector<float> norm, std::vector<int> params);

int main () {
	//Because there are three coordinates for each vertex,
	//each vector will have 3 times the number of vertices.
	std::vector<float> vertex, normals;
	std::vector<int> parameters;
	
	//desired_curve (parameters);
	
	calculate_vertex (vertex, normals, parameters);

	//print_to_obj ();

	return 0;
}

void calculate_vertex (std::vector<float> vert, std::vector<float> norm, std::vector<int> params) {
	switch (params[0]) {
		case 0:
			//calc_for_cylinder (vert, norm, params);
			break;
		
		case 1:
			//calc_for_sphere (vert, norm, params);
			break;
		
		case 2:
			//calc_for_torus (vert, norm, params);
			break;
		
		default:
			std::cout << "Not a valid curve!\n";
			abort ();
	}
}
