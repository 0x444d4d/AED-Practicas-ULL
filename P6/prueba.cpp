#include <cstdio>
#include <iostream>

#include <vector>

using namespace std;


class generator_t
{
private:
	const int base_;
	const int n_digits_;

	const char* output_ = "0123456789ABCDEF";

public:
	generator_t(const int base, const int n_digits):
	base_(base),
	n_digits_(n_digits)
	{}

	~generator_t(void) {}

	void generate(int i, vector<int>& sol)
	{
		if (i <= 0) 
			evaluate(sol);
	 	else {
	
			for(int j = 0; j < base_; j++){
				sol[i - 1] = j;
				generate(i - 1, sol);
			}
		}		
	}

	void generate(void)
	{
		vector<int> sol(n_digits_);
		generate(n_digits_, sol);
	}

	void evaluate(const vector<int>& sol)
	{
		for(int i = n_digits_ -1; i >= 0; i --)
			cout << output_[sol[i]];
		cout << endl;
	} 
};


int main(void)
{
	generator_t gen_bin(2, 4);
	gen_bin.generate();

	generator_t gen_hex(16, 4);
	gen_hex.generate();

	return 0;
}
