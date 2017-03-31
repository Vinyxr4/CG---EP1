#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

class Vertex {
	private:
//		float x, y, z;
	public:
		float X, Y, Z;
		float normal_x, normal_y, normal_z;

		Vertex (float x, float y, float z, float nx, float ny, float nz) {
			this->X = x;
			this->Y = y;
			this->Z = z;
			this->normal_x = nx;
			this->normal_y = ny;
			this->normal_z = nz;
		}

		float x (void);
		float y (void);
		float z (void);
		float nx (void);
		float ny (void);
		float nz (void);
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

float Vertex::nx (void) {
	return normal_x;
}
float Vertex::ny (void) {
	return normal_y;
}
float Vertex::nz (void) {
	return normal_z;
}

std::fstream output;
std::string output_name;

void calculate_vertex (std::vector<Vertex> *vertices, std::vector<int> params);
void print_to_obj (std::vector<Vertex> vertices, std::vector<int> params);
void correct_params (std::vector<int> params, int curve_id);
void calc_for_sphere (std::vector<Vertex> *vertices, std::vector<int> params);
void print_sphere (std::vector<Vertex> vertices, std::vector<int> params);
void desired_curve (std::vector<int> *params, int argc, char*argv[]);

int main (int argc, char *argv[]) {
	//Because there are three coordinates for each vertex,
	//each vector will have 3 times the number of vertices.
	std::vector<Vertex> vertices;
	std::vector<int> parameters;

	desired_curve (&parameters, argc, argv);
	parameters.push_back (1);
	parameters.push_back (100);
	parameters.push_back (100);
	calculate_vertex (&vertices, parameters);

	/*
	for (int i = 0; i < vertices.size (); ++i)
		std::cout << vertices[i].x() << " " << vertices[i].y() << " " << vertices[i].z() << "\n";
	*/

	print_to_obj (vertices, parameters);

	return 0;
}

void desired_curve (std::vector<int> *params, int argc, char*argv[]) {
	if (strcmp (argv[2], "cylinder") == 0) {
		params->push_back (0);
		params->push_back (atoi (argv[1]));
	}
	else if (strcmp (argv[3], "sphere") == 0) {
		params->push_back (1);
		params->push_back (atoi (argv[1]));
		params->push_back (atoi (argv[2]));
	}
	else if (strcmp (argv[4], "torus") == 0) {
		params->push_back (2);
		params->push_back (atoi (argv[1]));
		params->push_back (atoi (argv[2]));
		params->push_back (atoi (argv[2]));
	}
	output_name = argv[argc - 1];
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

	for (int j = params[1] - 1; j >= 0; --j) {
		for (int i = params[2] - 1; i >= 0; --i) {
			float x = cos (M_PI/2 + i * M_PI/ (params[2]-1)) * sin (j *2* M_PI / (params[1]));
			float y = sin (M_PI/2 + i * M_PI / (params[2]-1));
			float z = cos (M_PI/2 + i * M_PI/ (params[2]-1)) * cos (j *2 * M_PI / (params[1]));

			float mag = sqrt (x*x + y*y +z*z);
			float nx = x / mag;
			float ny = y / mag;
			float nz = z / mag;

			vertices->push_back (Vertex (x, y, z, nx, ny, nz));


			//std::cout << x << " " << y << " " << z << "\n";
		}
		//std::cout << "//\n";
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
	
	//for (int i = 0; i < vertices.size (); ++i)
	//	output << "vn " << vertices[i].nx() << " " << vertices[i].ny() << " "<< vertices[i].nz() << "\n";

	for (int i = 0; i < params[1]; ++i) {
		for (int j = 0; j < params[2] - 1; ++j) {
			if (i != params[1] - 1) {
				int x = 1 + i*params[2] + j;
				int y = 1 + (i+1)*params[2] + j + 1;
				int z = 1 + (i+1)*params[2] + j;
				int w = 1 + i*params[2] + j + 1;
				output << "f "<< x <<"/"<<x<<" "<<y<<"/"<<y<<" "<<z<<"/"<<z<< "\n";
				//output << "f "<<x<<" "<<y<<" "<<z<< "\n";
				output << "f "<< x <<"/"<<x<<" "<<w<<"/"<<w<<" "<<y<<"/"<<y<< "\n";
				//output << "f "<<x<<" "<<w<<" "<<y<< "\n";
			}
			else {
				int x = 1 + i*params[2] + j;
				int y = 1 + j + 1;
				int z = 1 + j;
				int w = 1 + i*params[2] + j + 1;
				output << "f "<< x <<"/"<<x<<" "<<y<<"/"<<y<<" "<<z<<"/"<<z<< "\n";
				//output << "f "<<x<<" "<<y<<" "<<z<< "\n";
				output << "f "<< x <<"/"<<x<<" "<<w<<"/"<<w<<" "<<y<<"/"<<y<< "\n";
				//output << "f "<<x<<" "<<w<<" "<<y<< "\n";
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
