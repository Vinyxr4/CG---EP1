#include "../lib/calc.h"

// Calculates the vertices of the desired shape and their normals,
// storing them into a vertex buffer.
void calculate_vertex (std::vector<Vertex> *vertices, std::vector<int> params) {
   switch (params[0]) {
      case 0:
         calc_for_cylinder (vertices, params);
         break;
      
      case 1:
         calc_for_sphere (vertices, params);
         break;
      
      case 2:
         calc_for_torus (vertices, params);
         break;
      
      default:
         std::cout << "Not a valid curve!\n";
         abort ();
   }  
}

// Calculates the vertices of the unit cylinder surface and their normals,
// storing them into a vertex buffer.
void calc_for_cylinder (std::vector<Vertex> *vertices, std::vector<int> params) {
      float height = 2;
      correct_params (params, params[0]);

      vertices->push_back (Vertex (0, -height/2, 0, 0, -1, 0));
      vertices->push_back (Vertex (0, height/2, 0, 0, 1, 0));
      for (int j = 0; j < 2; ++j) {
         for (int i = params[1] - 1; i >= 0; --i) {
            float x = sin (i * 2 * M_PI / (params[1]));
            float y = -height / 2;
            float z = cos (i * 2 * M_PI / (params[1]));  
            if (j == 0)
               vertices->push_back (Vertex (x, y, z, x, 0, z));
            else
               vertices->push_back (Vertex (x, y, z, 0, -1, 0));

         }
         for (int i = params[1] - 1; i >= 0; --i) {
            float x = sin (i * 2 * M_PI / (params[1]));
            float y = height / 2;
            float z = cos (i * 2 * M_PI / (params[1]));
            if (j == 0)
               vertices->push_back (Vertex (x, y, z, x, 0, z));
            else
               vertices->push_back (Vertex (x, y, z, 0, 1, 0));
         }
     }
}

// Calculates the vertices of the unit sphere surface and their normals,
// storing them into a vertex buffer.
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
      }
   }
}

// Calculates the vertices of the torus surface and their normals,
// storing them into a vertex buffer.
void calc_for_torus (std::vector<Vertex> *vertices, std::vector<int> params) {
   correct_params (params, params[0]);

   float R = 1.00;

   for (int i = 0; i < params[1]; ++i) {
      for (int j = 0; j < params[2]; ++j) {
         float x = (R + r * cos (j * 2 * M_PI / params[2])) * cos (i * 2 * M_PI / (params[1]));
         float y = r * sin (j * 2 * M_PI / params[2]);
         float z = (R + r * cos (j * 2 * M_PI / params[2])) * sin (i * 2 * M_PI / (params[1]));         

         float nx = r * cos (i * 2 * M_PI / (params[1])) * cos (j * 2 * M_PI / params[2]) * (R + r * cos (j * 2 * M_PI / params[2]));
         float ny = r * sin (j * 2 * M_PI / params[2]) * (R + r * cos (j * 2 * M_PI / params[2]));
         float nz = r * cos (j * 2 * M_PI / params[2]) * sin (i * 2 * M_PI / (params[1])) * (R + r * cos (j * 2 * M_PI / params[2]));

         vertices->push_back (Vertex (x, y, z, nx, ny, nz));
      }
   }
}



// Verifies if the parameters to create the mesh is correct.
void correct_params (std::vector<int> params, int curve_id) {
   switch (curve_id) {
      case 0:
         if (params[1] < 0) {
            std::cout << "Invalid arguments for cylinder!\n";
            abort ();
         }
         break;
      case 1:
         if (params[1] < 0 || params[2] < 0) {
            std::cout << "Invalid arguments for sphere!\n";
            abort ();
         }
         break;
      case 2:
         if (params[1] < 0 || params[2] < 0) {
            std::cout << "Invalid arguments for torus!\n";
            abort ();
         }
         break;
   }
}
