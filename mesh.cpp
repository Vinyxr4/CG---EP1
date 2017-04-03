
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

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

// Functions prototypes.
void calculate_vertex (std::vector<Vertex> *vertices, std::vector<int> params);
void print_to_obj (std::vector<Vertex> vertices, std::vector<int> params);
void correct_params (std::vector<int> params, int curve_id);
void calc_for_cylinder (std::vector<Vertex> *vertices, std::vector<int> params);
void calc_for_sphere (std::vector<Vertex> *vertices, std::vector<int> params);
void calc_for_torus (std::vector<Vertex> *vertices, std::vector<int> params);
void print_cylinder (std::vector<Vertex> vertices, std::vector<int> params);
void print_sphere (std::vector<Vertex> vertices, std::vector<int> params);
void print_torus (std::vector<Vertex> vertices, std::vector<int> params);
void desired_curve (std::vector<int> *params, int argc, char*argv[]);

// Global variable for the -r flag
float r = 0.00;

// Main function.
int main (int argc, char *argv[]) {
   std::vector<Vertex> vertices;
   std::vector<int> parameters;

   desired_curve (&parameters, argc, argv);

   calculate_vertex (&vertices, parameters);

   print_to_obj (vertices, parameters);

   return 0;
}

// Gets the argument line and treats it to get the arguments for the program.
void desired_curve (std::vector<int> *params, int argc, char*argv[]) {
   int curve, n, m;
   n = m = -1;

   for (int i = 1; i < argc; ++i) {
      if (strcmp (argv[i], "cylinder") == 0)
         curve = 0;
      else if (strcmp (argv[i], "sphere") == 0)
         curve = 1;
      else if (strcmp (argv[i], "torus") == 0)
         curve = 2;
      else if (strcmp (argv[i], "-n") == 0)
         n = atoi (argv[++i]);
      else if (strcmp (argv[i], "-m") == 0)
         m = atoi (argv[++i]);
      else if (strcmp (argv[i], "-r") == 0)
         r = atof (argv[++i]);
      else
         output_name = argv[i];
   }

   params->push_back (curve);
   params->push_back (n);
   params->push_back (m);
   params->push_back (r);
}

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

   if (r <= 0)
      r = 0.25;

   for (int i = 0; i < params[1]; ++i) {
      for (int j = 0; j < params[2]; ++j) {
         float x = (R + r * cos (j * 2 * M_PI / params[2])) * cos (i * 2 * M_PI / (params[1]));
         float y = (R + r * cos (j * 2 * M_PI / params[2])) * sin (i * 2 * M_PI / (params[1]));
         float z = r * sin (j * 2 * M_PI / params[2]);

         float nx = r * cos (i * 2 * M_PI / (params[1])) * cos (j * 2 * M_PI / params[2]) * (R + r * cos (j * 2 * M_PI / params[2]));
         float ny = r * cos (j * 2 * M_PI / params[2]) * sin (i * 2 * M_PI / (params[1])) * (R + r * cos (j * 2 * M_PI / params[2]));
         float nz = r * sin (j * 2 * M_PI / params[2]) * (R + r * cos (j * 2 * M_PI / params[2]));

         vertices->push_back (Vertex (x, y, z, nx, ny, nz));
      }
   }
}

// Prints the vertices buffer content onto a .obj file.
void print_to_obj (std::vector<Vertex> vertices, std::vector<int> params) {
   switch (params[0]) {
      case 0:
         print_cylinder (vertices, params);
         break;
      case 1:
         print_sphere (vertices, params);
         break;
      case 2:
         print_torus (vertices, params);
         break;
      default:
         std::cout << "Not a valid curve!\n";
         abort ();
   }
}

// Call of print_to_obj() for a cylinder shape.
void print_cylinder (std::vector<Vertex> vertices, std::vector<int> params) {
   output.open (output_name.c_str (), std::fstream::out);
   
   for (int i = 0; i < vertices.size (); ++i)
      output << "v " << vertices[i].x() << " " << vertices[i].y() << " "<< vertices[i].z() << "\n";
   
   for (int i = 0; i < vertices.size (); ++i)
      output << "vn " << vertices[i].nx() << " " << vertices[i].ny() << " "<< vertices[i].nz() << "\n";

   for (int i = 2; i < params[1] + 2; ++i) {
      int x = 1 + i;
      int y = 1 + params[1] + i + 1;
      int z = 1 + i + 1;
      int w = 1 + params[1] + i;
      if (i != params[1] + 1) {
         output << "f "<< x <<"//"<<x<<" "<<y<<"//"<<y<<" "<<z<<"//"<<z<< "\n";
         output << "f "<< x <<"//"<<x<<" "<<w<<"//"<<w<<" "<<y<<"//"<<y<< "\n";
      }
      else {
         output << "f "<< x <<"//"<<x<<" "<<y - i + 1<<"//"<<y - i + 1<<" "<<1 + 2<<"//"<<1 + 2<< "\n";
         output << "f "<< x <<"//"<<x<<" "<<y - 1<<"//"<<y - 1<<" "<<y - i + 1<<"//"<<y - i + 1<< "\n";
      }
   }

   for (int i = 2 + 2*params[1]; i < 2 + 4*params[1]; ++i) {
      int x = 1 + i;
      int y = x + 1;
      int k, l;
      if (i == 3*params[1] + 1)
         y = 1 + 2 + 2*params[1];
      else if (i == 4*params[1] + 1)
         y = 1 + 2 + 3*params[1];
         
      k = y, l = 1;
      if (i >= 2 + 3*params[1])
         k = 2, l = y;

      output << "f "<<x<<"//"<<x<<" "<<k<<"//"<<k<<" "<<l<<"//"<<l<< "\n";
   }

   output.close ();
}

// Call of print_to_obj() for a sphere shape.
void print_sphere (std::vector<Vertex> vertices, std::vector<int> params) {
   output.open (output_name.c_str (), std::fstream::out);
   
   for (int i = 0; i < vertices.size (); ++i)
      output << "v " << vertices[i].x() << " " << vertices[i].y() << " "<< vertices[i].z() << "\n";
   
   for (int i = 0; i < vertices.size (); ++i)
      output << "vn " << vertices[i].nx() << " " << vertices[i].ny() << " "<< vertices[i].nz() << "\n";

   for (int i = 0; i < params[1]; ++i) {
      for (int j = 0; j < params[2] - 1; ++j) {
         if (i != params[1] - 1) {
            int x = 1 + i*params[2] + j;
            int y = 1 + (i+1)*params[2] + j + 1;
            int z = 1 + (i+1)*params[2] + j;
            int w = 1 + i*params[2] + j + 1;
            output << "f "<< x <<"//"<<x<<" "<<y<<"//"<<y<<" "<<z<<"//"<<z<< "\n";
            output << "f "<< x <<"//"<<x<<" "<<w<<"//"<<w<<" "<<y<<"//"<<y<< "\n";
         }
         else {
            int x = 1 + i*params[2] + j;
            int y = 1 + j + 1;
            int z = 1 + j;
            int w = 1 + i*params[2] + j + 1;
            output << "f "<< x <<"//"<<x<<" "<<y<<"//"<<y<<" "<<z<<"//"<<z<< "\n";
            output << "f "<< x <<"//"<<x<<" "<<w<<"//"<<w<<" "<<y<<"//"<<y<< "\n";
         }
      }
   }

   output.close ();
}

// Call of print_to_obj() for a torus shape.
void print_torus (std::vector<Vertex> vertices, std::vector<int> params) {
   output.open (output_name.c_str (), std::fstream::out);
   
   for (int i = 0; i < vertices.size (); ++i)
      output << "v " << vertices[i].x() << " " << vertices[i].y() << " "<< vertices[i].z() << "\n";
   
   for (int i = 0; i < vertices.size (); ++i)
      output << "vn " << vertices[i].nx() << " " << vertices[i].ny() << " "<< vertices[i].nz() << "\n";

   int md = params[2] - 1;

   for (int i = 0; i < params[1]; ++i) {
      for (int j = 0; j < params[2]; ++j) {
         if (i != params[1] - 1) {
            int x = 1 + i*params[2] + j;
            int y = 1 + (i+1)*params[2] + (j % md) + 1;
            int z = 1 + (i+1)*params[2] + j;
            int w = 1 + i*params[2] + (j % md) + 1;
            output << "f "<< x <<"//"<<x<<" "<<z<<"//"<<z<<" "<<y<<"//"<<y<< "\n";
            output << "f "<< x <<"//"<<x<<" "<<y<<"//"<<y<<" "<<w<<"//"<<w<< "\n";
         }
         else {
            int x = 1 + i*params[2] + j;
            int y = 1 + (j % md) + 1;
            int z = 1 + j;
            int w = 1 + i*params[2] + (j % md) + 1;
            output << "f "<< x <<"//"<<x<<" "<<z<<"//"<<z<<" "<<y<<"//"<<y<< "\n";
            output << "f "<< x <<"//"<<x<<" "<<y<<"//"<<y<<" "<<w<<"//"<<w<< "\n";
         }
      }
   }

   output.close ();
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
      default:
         break;
   }
}
