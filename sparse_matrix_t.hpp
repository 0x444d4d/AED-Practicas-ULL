#pragma once

#include <iostream>

#include "template_matrix_t.hpp"
#include "sll_t.hpp"
#include "sll_node_t.hpp"
#include "vector_t.hpp"
#include "pair_t.hpp"
#include <cmath>

using namespace std;

namespace AED{

enum {COL_CONF, ROW_CONF};

//typedef vector_t<sll_t<pair_t>> sparse_t;

	class sparse_matrix_t {
	private:
		int m_; //filas
		int n_; //columnas
		int conf_;
    vector_t<sll_t<pair_t<double> > > sparse_;

	public:

		sparse_matrix_t(void) {}

		sparse_matrix_t(const matrix_t<double>& M, double eps, int conf):
    m_(M.get_m()), n_(M.get_n()), conf_(conf), sparse_() {
      fill(M, eps);
		}

		~sparse_matrix_t(void) {}

		ostream& write(ostream& os) {
      if (!conf_) cout << "configuracion por columnas" << endl;
      else cout << "configuracion por filas" << endl;
      os << "Numero de filas:" << setw(4) << m_ << endl;
      os << "Numero de columnas:" << setw(4) << n_ << endl;

			///////// (impresión de los elementos dispersos)
      for (short unsigned inx = 0; inx < sparse_.size(); ++inx) {
        sparse_[inx].write(os);
        os << endl;
      }
			return os;
		}

    bool is_zero(double val, double eps) {
      return ((fabs(val) < eps)? true : false); 
    }

    void mul(matrix_t<double> &M, matrix_t<double>&S);
    double get_at(short unsigned row, short unsigned col);
    void build(const matrix_t<double> &M, double eps, int conf);
    void fill(const matrix_t<double> &M, double eps);

    void set_m(int m) {m_ = m;}
    void set_n(int n) {n_ = n;}
    void set_conf(int conf) {conf_ = conf;}
    
    int get_m() {return m_;}
    int get_n() {return n_;}
    int get_conf() {return conf_;}

	};

  void sparse_matrix_t::build(const matrix_t<double> &M, double eps, int conf) {
    set_m(M.get_m());
    set_n(M.get_n());
    set_conf(conf);

    fill(M, eps);
  
  }

  void sparse_matrix_t::fill(const matrix_t<double> &M, double eps) {

    

    if (!conf_) {

      sparse_.resize(n_);

      for (short unsigned col = 0; col < n_; ++col)
          for (short unsigned row = 0; row < m_; ++row)
              if (!is_zero( M(row + 1, col + 1), eps )) {
                sparse_[col].insert_head( new sll_node_t<pair_t<double> >());
                sparse_[col].head()->set_data(pair_t<double>(row+1, M(row+1, col+1)));
              } 
    } else {

      sparse_.resize(m_);

      for (short unsigned row = 0; row < m_; ++row)
          for (short unsigned col = 0; col < n_ ; ++col)
              if (!is_zero( M(row + 1, col + 1), eps )) {
                sparse_[row].insert_head( new sll_node_t<pair_t<double> >());
                sparse_[row].head()->set_data(pair_t<double>(col+1, M(row+1, col+1)));
              } 
    }
  }


  void sparse_matrix_t::mul(matrix_t<double> &M, matrix_t<double> &S) {
  
    if (n_ == M.get_m()) {

      S.resize(m_, M.get_n());

      for(short unsigned row = 0; row < m_; ++row)
        for(short unsigned col= 0; col < M.get_n(); ++col)
          for(short unsigned itr = 0; itr < M.get_m(); ++itr)
	    if (double aux = get_at(row, itr))
            	S(row+1, col+1) += aux * M(itr+1, col+1);
            //cout << get_at(row, col);

    } else cout << "No es posible realizar la multiplicacion" << endl;

  }


  
  double sparse_matrix_t::get_at(short unsigned row, short unsigned col) {
    
    sll_node_t<pair_t<double> > *aux;
    if (!get_conf()) {
      
      aux = sparse_[col].head();
      while (aux != NULL) {
        if (aux->get_data().get_inx() == (row + 1)) {
          return  (aux->get_data().get_val());
        }
        aux = aux->get_next();
      }

    } else  aux = sparse_[row].head();

      aux = sparse_[row].head();
      while (aux != NULL) {
        if (aux->get_data().get_inx() == (col + 1)) {
          return  (aux->get_data().get_val());
        }
        aux = aux->get_next();
      }

    return 0;
  }
}
