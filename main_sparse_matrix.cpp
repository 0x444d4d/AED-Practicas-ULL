#include <iostream>
#include <fstream>
#include <cstdlib>

#include "sparse_matrix_t.hpp"
#include "template_matrix_t.hpp"

using namespace std;
using namespace AED;

void print_menu(void);


int main (void)
{
	matrix_t<double> M, N;
  ofstream inFile("prueba.txt");

	M.read(cin);

	sparse_matrix_t SM(M, 1E-3, COL_CONF);

	SM.write(cout);

  SM.mul(M, N);

  N.write(cout);

  //SN = SM;
 
}


void print_menu(void) {
  system("clear");
  cout << "1.- Cargar matriz" << endl;
  cout << "2.- Mostrar matriz" << endl;
  cout << "3.- Multiplicar matriz" << endl;
  cout << "4.- Salir" << endl;
}



