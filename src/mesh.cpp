//Students:                 | NUSP

//Patrick Abrahão Menani    | 8941050
//Vinícius Pessoa Duarte    | 8941043

#include <vector>
#include <string>
#include <cstring>
#include "../lib/Vertex.h"
#include "../lib/global.h"
#include "../lib/print.h"
#include "../lib/calc.h"


// Functions prototypes.
void desired_curve (std::vector<int> *params, int argc, char*argv[]);

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
