#include "matrix.hpp"
#include <iomanip>
#include <string>

class RelaxationMethod : public Matrix{
private:
    long double *x;
    long double eps;

    int cell_width;
    int num_after_point;
    int size;
public:
    //Constructor
    RelaxationMethod(long double x[], int size, long double eps = 1e-10, int cell_width = 20, int num_after_point=10): Matrix(){
        this->x = new long double[size];
        this->size = size;
        this->eps = eps;
        this->cell_width = cell_width;
        this->num_after_point = num_after_point;
        std::copy(x, x+size, this->x);
    }
    RelaxationMethod(int size, long double eps = 1e-10, int cell_width = 20, int num_after_point=10): Matrix(){
        this->x = new long double[size];
        for(int i = 0; i < size; i++) {x[i] = 0;}
        this->size = size;
        this->eps = eps;
        this->cell_width = cell_width;
        this->num_after_point = num_after_point;
    }

    //find answer
    long double* findAnswer(long double w = 0.5, int iterations = 1000, long double eps = 1e-10){
        long double sum1, sum2, old_x;
        print();
        for (int iter = 0; iter < iterations; iter++){
            for(int i = 0; i < size; i++){
                sum1 = 0; sum2 = 0;
                for(int j = 0; j < size; j++){
                    if (j < i){
                        sum1 += matrixA[i][j] * x[j];
                    }
                    else if (j > i){
                        sum2 += matrixA[i][j] * x[j];
                    }
                }
                old_x = x[i];
                x[i] = (1-w)*x[i] + w*(matrixB[i] - sum1 - sum2)/matrixA[i][i];
                print(false);
            }
            if (abs(old_x - x[size - 1]) < eps){
                std::cout << "Answer found!" << std::endl;
                std::cout << "count of iteration = " << iter << std::endl; 
                print();
                break;
            }
        }   
        return x;     
    }

    void print(bool withHead = true) const {
        if (withHead){
            for(int i = 0; i < size; i++){
                std::cout << "|";
                std::cout << std::setw(cell_width) << "x" << i+1;
            }
            std::cout << "|" << std::endl;
            std::cout << std::string(size * cell_width + size * 2 + 1, '-') << std::endl;
        }
        for(int i = 0; i < size; i++){
            std::cout << "|";
            if (std::abs(x[i]) < eps) std::cout << std::setprecision(num_after_point) << std::setw(cell_width + 1) << 0;
            else std::cout << std::setprecision(num_after_point) << std::setw(cell_width + 1) << x[i];
        }
        std::cout << "|" << std::endl;
    }

};