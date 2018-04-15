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
    //sparse_t sparse_;
    vector_t<sll_t<pair_t<double> > > sparse_;

		// Aquí va la definición de la estructura dispersa: dispersa_
	public:

		sparse_matrix_t(const matrix_t<double>& M, double eps, int conf):
       m_(M.get_m()), n_(M.get_n()), conf_(conf), sparse_()
    {
      if (!conf) {

        sparse_.resize(n_);

        for (short unsigned col = 0; col < n_; ++col)
            for (short unsigned row = 0; row < m_; ++row)
                if (!is_zero( M(row + 1, col + 1), eps )) {
                  sparse_[col].insert_head( new sll_node_t<pair_t<double> >());
                  sparse_[col].head()->set_data(pair_t<double>(row+1, M(row+1, col+1)));
                } 
      //sparse_[0].write(cout);
      } else {

        sparse_.resize(m_);

        for (short unsigned row = 0; row < m_; ++row)
            for (short unsigned col = 0; col < n_; ++col)
                if (!is_zero( M(row + 1, col + 1), eps )) {
                  sparse_[row].insert_head( new sll_node_t<pair_t<double> >());
                  sparse_[row].head()->set_data(pair_t<double>(col+1, M(row+1, col+1)));
                } 
      }
		}

		~sparse_matrix_t(void) {}

		ostream& write(ostream& os)
		{
      os << "Numero de filas:" << setw(4) << m_ << endl;
      os << "Numero de columnas:" << setw(4) << n_ << endl;
			///////// (impresión de los elementos dispersos)
      for (short unsigned inx = 0; inx < sparse_.size(); ++inx) {
        sparse_[0].write(os);
        os << endl;
      }

			return os;
		}

    bool is_zero(double val, double eps) {
      return ((fabs(val) < eps)? true : false); 
    }
    
			
    sparse_matrix_t& operator=(sparse_matrix_t &sm) {

      m_ = sm.m_;
      n_ = sm.n_;
      conf_ = sm.conf_;
      sparse_ = sm.sparse_;

      return *this;
    }


	};
}
