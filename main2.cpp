#include <iostream>
#include <fstream>
#include <cstdlib>

#include "sparse_matrix_t.hpp"
#include "template_matrix_t.hpp"

using namespace std;
using namespace AED;

void print_menu(void);
char read_key(void);


int main (void) {
  matrix_t<double> M, N;
  int selector;
  sparse_matrix_t SM;


  while (1) {
    system("clear");
    print_menu();
    cin >> selector;
    getchar();

    switch(selector) {
      case 1: 
        system("clear");
        M.read(cin);
        SM.build(M, 1E-3, ROW_CONF);

        break;
    
      case 2: 
        system("clear");
        SM.write(cout);
        getchar();
        break;

      case 3: 
        system("clear");
        cout << "Carga la matriz densa" << endl;
        M.read(cin);
        SM.mul(M,N);
        system("clear");
        cout  << "RESULTADO:" << endl;
        N.write(cout);
        getchar();
        getchar();
        break;

      case 4: 
        exit(0);
        break;

      default:
        cout << "El caracter introducido no es valido";
    }
  }
}


void print_menu(void) {
  system("clear");
  cout << "1.- Cargar matriz" << endl;
  cout << "2.- Mostrar matriz" << endl;
  cout << "3.- Multiplicar matriz" << endl;
  cout << "4.- Salir" << endl;
}

char read_key(void) {
  return getchar();
}


