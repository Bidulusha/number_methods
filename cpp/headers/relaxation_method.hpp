#include "matrix.hpp"



class RelaxationMethod : public Matrix{
private:
    long double *x0;
public:
    //Constructor
    RelaxationMethod(long double x[], int size): Matrix(){
        x0 = new long double[size];
        std::copy(x, x+size, x0);
    }

    //find answer
    long double* find_answer(int iterations = 1000, long double eps = 1e-10){
        for (int i = 0; i < iterations; i++){
            
        }        
    }

};