#include <iostream>
#include <fstream>
#include "stack_v_t.hpp"

using namespace std;

void load(ifstream &inFile, stack_m &M);
bool equilibrada(void);

int main(void)
{
  stack_m M(34, 34);
  ifstream inFile;
  inFile.open("quijote.txt");

  load(inFile, M);
  while( !M.empty() )
  {
    cout << M.top();
    M.pop();  
  }
  cout << endl;

  cout << equilibrada();
}

void load(ifstream &inFile, stack_m &M)
{
  char aux;
  while (inFile >> noskipws >> aux && !M.full())
  {
    M.push(aux);
  }
}

bool equilibrada(void)
{
  string inString;
  cin >> inString;
  stack_m M(1,inString.size());

  //if (inString[0] == ')') return false;
  for (unsigned inx = 0; inx < inString.size(); ++inx)
  {
    if (inString[inx] == '(') M.push(')');
    if (inString[inx] == ')' && M.pop()) return false;//M.pop();
    //if (inString[inx] == ')') M.pop();
    //if (inString[inx] == ')' && M.empty) return false;
  }   

  return M.empty();

}
