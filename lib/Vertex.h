//Students:                 | NUSP

//Patrick Abrahão Menani    | 8941050
//Vinícius Pessoa Duarte    | 8941043

#include "global.h"

#ifndef VERTEX_H
#define VERTEX_H

// Class that abstracts a vertex and it's normal.
class Vertex {
   private:
   float X, Y, Z;
   float normal_x, normal_y, normal_z;
   public:
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

#endif
