#include <iostream>
#include <fstream>

#include "sparse_matrix_t.hpp"
#include "template_matrix_t.hpp"

using namespace std;
using namespace AED;


int main (void)
{
	matrix_t<double> M;
  ofstream inFile("prueba.txt");

	M.read(cin);

	sparse_matrix_t SM(M, 1E-3, COL_CONF);
  sparse_matrix_t SN();

  //SN = SM;
 
	SM.write(cout);
}




