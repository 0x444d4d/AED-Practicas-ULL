#pragma once

#include "template_matrix_t.hpp"
namespace  AED
{
class stack_m
{
  private:
  int m_;
  int n_;
  int top_;
  matrix_t<char> stack_;


  public:

  stack_m(int m, int n): top_(-1), m_(m), n_(n), stack_(m, n) {}
  ~stack_m(void) {};


  bool full(void) {return (top_ == (m_ * n_));}
  bool empty(void) {return (top_ == -1);}


  bool push(char aux);
  bool pop(void);
  char top(void) {return stack_(inx_to_row(top_), inx_to_col(top_));}
  bool flush(void) {top_ = -1;}

  private:

  unsigned int inx_to_row(int inx) {return (( inx / n_) + 1);}
  unsigned int inx_to_col(int inx) {return (( inx % n_) + 1);}
};
}

using namespace AED
{
bool stack_m::push(char aux)
{
  if(!full()) {
    ++top_;
    stack_(inx_to_row(top_),inx_to_col(top_)) = aux;
    return true;
  } else return false;
}

bool stack_m::pop(void)
{
  if (!empty()) {
    --top_; 
    return true;
  } else return false;
}

void stack_m::resize(int m, int n)
{
  m_ = m;
  n_ = n;
  top_ = -1;
  stack_.resize(m,n);
}
}
