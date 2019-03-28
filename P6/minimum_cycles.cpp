#include <limits>
#include <cstdlib>
#include <time.h>
#include "vector.hpp"

using namespace std;

class minimum_cycles
{
private:

  const int n_;
  vector<int> sol_;
  int best_value_;
  vector<int> best_sol_;
  vector<int> id_;
  vector<int> od_;


public:

//Constructores; Destructores
  minimum_cycles(int n): n_(n), sol_(n*n), best_sol_(n*n), id_(n), od_(n)
  {
    for (unsigned int inx = 0; inx < n_*n_; ++inx) {
      sol_[inx] = 0;
      best_sol_[inx] = 0;//numeric_limits<int>::max();
    }  

    best_value_ = numeric_limits<int>::max();

  }


  ~minimum_cycles(void) {}


//Metodos publicos  
  void compute_best_cycle(const vector<int>& cost)
  {
    generate(n_ * n_, cost);
  }

  void compute_best_cycle(const vector<int>& cost, int lenght)
  {
    cout << "sobrecargada";
    generate(n_ * n_, cost, lenght);
  }

  void write(ostream& os)
  {
    for (unsigned row = 0; row < n_; ++row) {
      os << endl;
      for (unsigned col = 0; col < n_; ++col)
	os << best_sol_[pos(row, col)] << " ";
    }
  }

  void generate(int i, const vector<int>& cost)
  {
    if (i <= 0) {

       vector<int> id(n_);
       vector<int> od(n_);
       compute_degree(id, od);

       if (no_diag() && is_cycle(id, od)) evaluate(cost);
    }
    else {

      sol_[i - 1] = 1;
      generate(i - 1, cost);
      sol_[i - 1] = 0;
      generate(i - 1, cost);
    }

  }

 void generate(int i, const vector<int>& cost, int lenght)
  {
    unsigned sum = 0;
    if (i <= 0) {

       vector<int> id(n_);
       vector<int> od(n_);
       compute_degree(id, od);

       for (unsigned inx = 0; inx < n_; ++inx)
       	 sum += id[inx];

       if (no_diag() && is_cycle(id, od) && lenght == sum) evaluate(cost);

    }
    else {

      sol_[i - 1] = 1;
      generate(i - 1, cost, lenght);
      sol_[i - 1] = 0;
      generate(i - 1, cost, lenght);
    }

  }



  int pos(int i, int j) const 
  {
    return (i * n_) + j;
  }
  
  bool no_diag(void) 
  {
    for (unsigned inx = 0; inx < n_; ++inx)
      if (sol_[pos(inx, inx)]) return false;

    return true;
  }

  void compute_in_degree(vector<int>& id)
  {
    for (unsigned row= 0; row < n_; ++row){
      id[row] = 0;
      for (unsigned col= 0; col < n_; ++col)
        id[row] += sol_[pos(row, col)];
    }
        
  }

  void compute_out_degree(vector<int>& od)
  {
    for (unsigned row= 0; row < n_; ++row) {
      od[row] = 0;
      for (unsigned col = 0; col < n_; ++col)
        od[row] += sol_[pos(col, row)];
    }
  }

  void compute_degree(vector<int>& id, vector<int>& od)
  {
    compute_in_degree(id);
    compute_out_degree(od);
  }

  bool is_cycle(vector<int>& id, vector<int>& od)
  {
    //compute_degree(id, od);

    for (unsigned inx = 0; inx < n_; ++inx) {
      //cout << "test: inx = "<< inx << endl;

      if (id[inx] != od[inx]) return false;
      if (id[inx] > 1 || od[inx] > 1) return false;
    }
    return true;
  }

  void evaluate(const vector<int>& cost)
  {
    int ccost = 0;
    for(int i = n_ * n_ - 1; i >= 0; i--)
      ccost += cost[i] * sol_[i];

    if (ccost < best_value_) {
      best_value_ = ccost;
      best_sol_ = sol_;
    }
  }


};
    

void print_menu(void);


int main(void)
{

  int nodes = 0;
  int lenght = 0;
  unsigned short selector;
  
  cout << "Escriba el numero de nodos que tendra el grafo: ";
  cin >> nodes;
  cin.get();
  minimum_cycles mc(nodes);
  vector<int> cost(nodes * nodes);
 

  while(1)
  {
    print_menu();
    std::cin >> selector;
    std::cin.get();

    switch(selector)
    {
      case 1:
        system("clear");
        srand(time(NULL));
          for(int i = 0; i < (nodes * nodes); i++) {
            cost[i] = ((rand() - rand()) % 10);
          }
      break;

      case 2:
        system("clear");
          for(int i = 0; i < (nodes * nodes); i++) {
            cout << cost[i] << " ";
          }
        cin.get();
      break;

      case 3:
        system("clear");
        mc.compute_best_cycle(cost);
      break;

      case 4:
        system("clear");
        mc.write(cout);
        cin.get();
      break;

      case 5:
        system("clear");
        cin >> lenght; 
        cin.get();
        mc.compute_best_cycle(cost, lenght);
        mc.write(cout);
        cin.get();
      break;

      case 6:
        system("clear");
        exit(0);
    }
  }
  return 0;
}

void print_menu(void)
{
  system("clear");
  std::cout << "\t\tMenu" << std::endl;
  std::cout << "1.- Generar matriz de costes" << std::endl;
  std::cout << "2.- Imprimir matriz de costes." << std::endl;
  std::cout << "3.- Calcular recorrido optimo" << std::endl;
  std::cout << "4.- Imprimir recorrido optimo." << std::endl;
  std::cout << "5.- Recorrido minimo de tamaño 'n'." << std::endl;
  std::cout << "6.- Salir del programa." << std::endl;
}
