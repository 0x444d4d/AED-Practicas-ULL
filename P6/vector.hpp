#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cassert>


using namespace std;

template <class T>
class vector
{
private:
      T*      v_;
      int     sz_;

public:

      vector(void):
            v_(NULL),
            sz_(0) {}

      vector(int sz):
            v_(NULL),
            sz_(sz)
      {
            crea_vector();
      }

      vector(const vector<T>& v):
            v_(NULL),
            sz_(v.sz_)
      {
            crea_vector();

            for(int i = 0; i < sz_; i++)
                  v_[i] = v.v_[i];
      }

      ~vector(void)
      {
            destruye_vector();
      }

      vector<T>& operator=(const vector<T>& v)
      {
            destruye_vector();
            sz_ = v.sz_;
            crea_vector();

            for(int i = 0; i < sz_; i++)
                  v_[i] = v.v_[i];

            return *this;
      }

      int size(void) const
      {
            return sz_;
      }

      const T& at(int pos) const
      {
            assert((pos < sz_) && ((pos >= 0)));
            return v_[pos];
      }

      T& at(int pos)
      {
            assert((pos < sz_) && ((pos >= 0)));
            return v_[pos];
      }

      const T& operator[](int pos) const
      {
            return at(pos);
      }

      T& operator[](int pos)
      {
            return at(pos);
      }

      void rezize(unsigned int size) {
        destruye_vector();
        sz_ = size;
        crea_vector();
      
      }

private:

      void crea_vector(void)
      {
            v_ = new T[sz_];
      }

      void destruye_vector(void)
      {
            if (v_ != NULL) {
                  delete [] v_;
                  v_ = NULL;
            }
      }
};


