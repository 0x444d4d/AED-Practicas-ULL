#include <iostream>
#include <fstream>
#include "stack_m_t.hpp"

using namespace std;

void print_menu(void);
void load(istream &is, stack_m &M);
void load(stack_m &M);
bool equilibrada(void);
void print_stack(stack_m &M);

int main(void)
{
  stack_m M(34, 34);
  string filename;
  ifstream inFile;
  int selector;

  while(1)
  {
    print_menu();
    std::cin >> selector;
    std::cin.get();
    switch(selector)
    {
      case 1:
        system("clear");
        std::cin >> filename;
        std::cin.get();
        inFile.open(filename);
        load(inFile, M);
        std::cin.get();
      break;

      case 2:
        system("clear");
        load(M);
        std::cin.get();
      break;

      case 3:
        system("clear");
        print_stack(M);
        std::cin.get();
      break;

      case 4:
        system("clear");
        if (!equilibrada())
          std::cout << "Los parantesis no estan equilibrados.";
        else
          std::cout << "Los parentesis estan equilibrados.";
        std::cin.get();
      break;

      case 5:
        system("clear");
        exit(0);
    }
  }

  std::cout << equilibrada();
}

void load(istream &is, stack_m &M)
{
  char aux;
  //while (is >> std::noskipws >> aux && !M.full())
  //{
   // M.push(aux);
  //}
  M.flush();
  while (is >> std::noskipws >> aux && M.push(aux));
}


void load(stack_m &M)
{
  string inString;
  std::cin >> inString;
  std::cin.get();
  //stack_m M(1,inString.size());

  M.flush();
  for (unsigned inx = 0; inx < inString.size(); ++inx)
  {
    M.push(inString[inx]);
  }
}


bool equilibrada(void)
{
  string inString;
  std::cin >> inString;
  std::cin.get();
  stack_m S(1,inString.size());

  //if (inString[0] == ')') return false;
  for (unsigned inx = 0; inx < inString.size(); ++inx)
  {
    if (inString[inx] == '(') S.push(')');
    if (inString[inx] == ')' && !S.pop()) return false;//M.pop();
    //if (inString[inx] == ')') M.pop();
    //if (inString[inx] == ')' && M.empty) return false;
  }   

  return S.empty();
}

void print_menu(void)
{
  system("clear");
  std::cout << "\t\tMenu" << std::endl;
  std::cout << "1.- Cargar pila desde fichero." << std::endl;
  std::cout << "2.- Cargar pila desde teclado." << std::endl;
  std::cout << "3.- Imprimir pila" << std::endl;
  std::cout << "4.- Comprobar parentesis." << std::endl;
  std::cout << "5.- Salir del programa." << std::endl;
}


void print_stack(stack_m &M)
{
  while( !M.empty() )
  {
    std::cout << M.top();
    M.pop();  
  }
}
