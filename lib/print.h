//Students:                 | NUSP

//Patrick Abrahão Menani    | 8941050
//Vinícius Pessoa Duarte    | 8941043

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "Vertex.h"
#include "global.h"

#ifndef PRINT_H
#define PRINT_H

// Prints the vertices buffer content onto a .obj file.
void print_to_obj (std::vector<Vertex> vertices, std::vector<int> params);

// Call of print_to_obj() for a cylinder shape.
void print_cylinder (std::vector<Vertex> vertices, std::vector<int> params);

// Call of print_to_obj() for a sphere shape.
void print_sphere (std::vector<Vertex> vertices, std::vector<int> params);

// Call of print_to_obj() for a torus shape.
void print_torus (std::vector<Vertex> vertices, std::vector<int> params);

#endif
