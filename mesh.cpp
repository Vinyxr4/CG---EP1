
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

class Vertex {
   private:
//    float x, y, z;
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
void calc_for_cylinder (std::vector<Vertex> *vertices, std::vector<int> params);
void calc_for_sphere (std::vector<Vertex> *vertices, std::vector<int> params);
void print_cylinder (std::vector<Vertex> vertices, std::vector<int> params);
void print_sphere (std::vector<Vertex> vertices, std::vector<int> params);
void desired_curve (std::vector<int> *params, int argc, char*argv[]);

int main (int argc, char *argv[]) {
   //Because there are three coordinates for each vertex,
   //each vector will have 3 times the number of vertices.
   std::vector<Vertex> vertices;
   std::vector<int> parameters;

   desired_curve (&parameters, argc, argv);

   calculate_vertex (&vertices, parameters);

   /*
   for (int i = 0; i < vertices.size (); ++i)
      std::cout << vertices[i].x() << " " << vertices[i].y() << " " << vertices[i].z() << "\n";
   */

   print_to_obj (vertices, parameters);

   return 0;
}

void desired_curve (std::vector<int> *params, int argc, char*argv[]) {
   int curve, n, m, r;
   n = m = r = -1;


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
         r = atoi (argv[++i]);
      else
         output_name = argv[i];
   }
   //std::cout << output_name << "\n";
   params->push_back (curve);
   params->push_back (n);
   params->push_back (m);
   params->push_back (r);


   /*
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
   output_name = argv[argc - 1];*/
}
   
void calculate_vertex (std::vector<Vertex> *vertices, std::vector<int> params) {
   switch (params[0]) {
      case 0:
         calc_for_cylinder (vertices, params);
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

// Calculates the vertices of the unit cylinder surface and their normals,
// storing them into a vertex buffer.
void calc_for_cylinder (std::vector<Vertex> *vertices, std::vector<int> params) {
      float height = 2;
      //correct_params (params, params[0]);

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
         //print_torus (vertices, params);
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

void correct_params (std::vector<int> params, int curve_id) {
   switch (curve_id) {
      case 0:
         if (params[1] < 0) {
            std::cout << "Invalid arguments for sphere!\n";
            abort ();
         }
      case 1:
         if (params[1] < 0 || params[2] < 0) {
            std::cout << "Invalid arguments for sphere!\n";
            abort ();
         }
      default:
         break;
   }
}