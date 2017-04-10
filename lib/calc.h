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

void calculate_vertex (std::vector<Vertex> *vertices, std::vector<int> params);
void correct_params (std::vector<int> params, int curve_id);
void calc_for_cylinder (std::vector<Vertex> *vertices, std::vector<int> params);
void calc_for_sphere (std::vector<Vertex> *vertices, std::vector<int> params);
void calc_for_torus (std::vector<Vertex> *vertices, std::vector<int> params);

#endif
