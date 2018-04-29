#include <iostream>
#include <fstream>
#include "stack_v_t.hpp"

using namespace std;
void load(ifstream &inFile, stack_m &M);

int main(void)
{
  stack_m M(50, 30);
  ifstream inFile;
  inFile.open("quijote.txt");

  load(inFile, M);
  while( !M.empty() )
  {
    cout << M.top();
    M.pop();  
  }
}

void load(ifstream &inFile, stack_m &M)
{
  char aux;
  while (inFile >> noskipws >> aux && !M.full())
  {
    M.push(aux);
  }
}
