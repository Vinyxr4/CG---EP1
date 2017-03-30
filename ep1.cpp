#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

class Vertex {
	private:
//		float x, y, z;
	public:
		float X, Y, Z;
		float normal_x, normal_y, normal_z;

		Vertex (float x, float y, float z) {
			this->X = x;
			this->Y = y;
			this->Z = z;
		}

		float x (void);
		float y (void);
		float z (void);
};

float Vertex::x (void) {
	return X;
}
float Vertex::y (void) {
	return Y;
}
float Vertex::z (void) {
	return Z;
}

std::fstream output;
std::string output_name;

void calculate_vertex (std::vector<Vertex> *vertices, std::vector<int> params);
void print_to_obj (std::vector<Vertex> vertices, std::vector<int> params);
void correct_params (std::vector<int> params, int curve_id);
void calc_for_sphere (std::vector<Vertex> *vertices, std::vector<int> params);
void print_sphere (std::vector<Vertex> vertices, std::vector<int> params);
void desired_curve (std::vector<int> *params);

int main () {
	//Because there are three coordinates for each vertex,
	//each vector will have 3 times the number of vertices.
	std::vector<Vertex> vertices;
	std::vector<int> parameters;

	desired_curve (&parameters);
	parameters.push_back (1);
	parameters.push_back (100);
	parameters.push_back (100);
	calculate_vertex (&vertices, parameters);

	/*
	for (int i = 0; i < vertices.size (); ++i)
		std::cout << vertices[i].x() << " " << vertices[i].y() << " " << vertices[i].z() << "\n";
	*/
	
	output_name = "teste.obj";
	print_to_obj (vertices, parameters);

	return 0;
}

void desired_curve (std::vector<int> *params) {
	std::string token;
	std::cin >> token;
	std::cout << token << "\n";
}
	
void calculate_vertex (std::vector<Vertex> *vertices, std::vector<int> params) {
	switch (params[0]) {
		case 0:
			//calc_for_cylinder (vert, norm, params);
			break;
		
		case 1:
			calc_for_sphere (vertices, params);
			break;
		
		case 2:
			//calc_for_torus (vert, norm, params);
			break;
		
		default:
			std::cout << "Not a valid curve!\n";
			abort ();
	}
}

/* Parametric equations for the sphere (unit radius):
	x = sqrt (1 - cos (phi)^2) * cos (theta); 	cos(theta) * sqrt(1 - cos(phi)^2)^-1 * cos(phi) * sin(phi) || -sin(theta) * sqrt (1 - cos (phi)^2)
	y = sqrt (1- cos (phi)^2) * sin (theta);
	z = cos (phi);	
*/

void calc_for_sphere (std::vector<Vertex> *vertices, std::vector<int> params) {
	correct_params (params, params[0]);

	for (int i = 0; i < params[1]; ++i) {
		for (int j = 0; j < params[2]; ++j) {
			float x = sqrt (1 - pow (cos (j * M_PI/ (params[2] - 1)), 2)) * cos (i * 2 * M_PI / (params[1]));
			float y = sqrt (1 - pow (cos (j * M_PI/ (params[2] - 1)), 2)) * sin (i * 2 * M_PI / (params[1]));
			float z = cos (j * M_PI / (params[2] - 1));

			vertices->push_back (Vertex (x, y, z));

			//std::cout << x << " " << y << " " << z << "\n";
		}
	}
}

void print_to_obj (std::vector<Vertex> vertices, std::vector<int> params) {
	switch (params[0]) {
		case 0:
			//print_cylinder (vertices, params);
			break;
		case 1:
			print_sphere (vertices, params);
			break;
		case 2:
			//print_torus (vertices, params);
			break;
		default:
			std::cout << "Not a valid curve!\n";
			abort ();
	}
}


void print_sphere (std::vector<Vertex> vertices, std::vector<int> params) {
	output.open (output_name.c_str (), std::fstream::out);
	
	for (int i = 0; i < vertices.size (); ++i)
		output << "v " << vertices[i].x() << " " << vertices[i].y() << " "<< vertices[i].z() << "\n";

	for (int i = 0; i < params[1]; ++i) {
		for (int j = 0; j < params[2] - 1; ++j) {
			if (i != params[1] - 1) {
				output << "f " << 1 + i*params[2] + j << " " << 1 + (i+1)*params[2] + j << " "<< 1 + (i+1)*params[2] + j + 1 << "\n";
				output << "f " << 1 + i*params[2] + j << " " << 1 + i*params[2] + j + 1 << " "<< 1 + (i+1)*params[2] + j + 1 << "\n";
			}
			else {
				output << "f " << 1+ i*params[2] + j << " " << 1 + j << " "<< 1 + j + 1 << "\n";
				output << "f " << 1 + i*params[2] + j << " " << 1 + i*params[2] + j + 1 << " "<< 1 + j + 1 << "\n";
			
			}
		}
	}

	output.close ();
}

void correct_params (std::vector<int> params, int curve_id) {
	switch (curve_id) {
		case 1:
			if (params.size () < 3) {
				std::cout << "Invalid number of arguments for sphere!\n";
				abort ();
			}
		default:
			break;
	}
}
