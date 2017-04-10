//Students:                 | NUSP

//Patrick Abrahão Menani    | 8941050
//Vinícius Pessoa Duarte    | 8941043

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Vertex.h"
#include <cmath>
#include "global.h"

#ifndef CALC_H
#define CALC_H

// Calculates the vertices of the desired shape and their normals,
// storing them into a vertex buffer.
void calculate_vertex (std::vector<Vertex> *vertices, std::vector<int> params);

// Calculates the vertices of the unit cylinder surface and their normals,
// storing them into a vertex buffer.
void calc_for_cylinder (std::vector<Vertex> *vertices, std::vector<int> params);

// Calculates the vertices of the unit sphere surface and their normals,
// storing them into a vertex buffer.
void calc_for_sphere (std::vector<Vertex> *vertices, std::vector<int> params);

// Calculates the vertices of the torus surface and their normals,
// storing them into a vertex buffer.
void calc_for_torus (std::vector<Vertex> *vertices, std::vector<int> params);

// Verifies if the parameters to create the mesh is correct.
void correct_params (std::vector<int> params, int curve_id);

#endif
