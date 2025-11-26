#include <iostream>
#include "headers/matrix.hpp"
#include "headers/cramers_rule.hpp"
#include "headers/invertible_matrix.hpp"


int main(){
    // CramersMatrix cramerMatrix;
    // long double * variables = cramerMatrix.FindVariables();
    // std::cout << cramerMatrix.GetDeterminant() <<  std::endl;

    // std::cout << "Variables is" << std::endl;
    // for (int i = 0; i < cramerMatrix.Size(); i++){
    //     std::cout << "x" << i << " = " << variables[i] << std::endl;
    // }

    // cramerMatrix.CheckAnswer();
    InvertibleMatrix invertibleMatrix;
    
    Matrix inverseMatrix = invertibleMatrix.findInverseMatrix(10000);
    
    std::cout << "Inverse matrix:" << std::endl;
    inverseMatrix.Print();
    
    std::cout << "Verification (A * A⁻¹):" << std::endl;
    Matrix check = invertibleMatrix.matrix() * inverseMatrix;
    check.Print();

    return 0;
}



/*
3
2 0 -1 -3
-1 3 1 2
1 -1 4 4
*/