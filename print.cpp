#include "lib/print.h"

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
            output << "f "<< y <<"//"<<y<<" "<<z<<"//"<<z<<" "<<x<<"//"<<x<< "\n";
            output << "f "<< w <<"//"<<w<<" "<<y<<"//"<<y<<" "<<x<<"//"<<x<< "\n";
         }
         else {
            int x = 1 + i*params[2] + j;
            int y = 1 + (j % md) + 1;
            int z = 1 + j;
            int w = 1 + i*params[2] + (j % md) + 1;
            output << "f "<< y <<"//"<<y<<" "<<z<<"//"<<z<<" "<<x<<"//"<<x<< "\n";
            output << "f "<< w <<"//"<<w<<" "<<y<<"//"<<y<<" "<<x<<"//"<<x<< "\n";
         }
      }
   }

   output.close ();
}
