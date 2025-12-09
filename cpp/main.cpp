#include <iostream>
#include "headers/matrix.hpp"
#include "headers/cramers_rule.hpp"
#include "headers/invertible_matrix.hpp"
#include "headers/relaxation_method.hpp"

int main(){
    // CramersMatrix cramerMatrix;
    // long double * variables = cramerMatrix.FindVariables();
    // std::cout << cramerMatrix.GetDeterminant() <<  std::endl;

    // std::cout << "Variables is" << std::endl;
    // for (int i = 0; i < cramerMatrix.Size(); i++){
    //     std::cout << "x" << i << " = " << variables[i] << std::endl;
    // }

    // cramerMatrix.CheckAnswer();

    // InvertibleMatrix invertibleMatrix;
    
    // Matrix inverseMatrix = invertibleMatrix.findInverseMatrix(10000);
    
    // std::cout << "Inverse matrix:" << std::endl;
    // inverseMatrix.Print();
    
    // std::cout << "Verification (A * A⁻¹):" << std::endl;
    // Matrix check = invertibleMatrix.matrix() * inverseMatrix;
    // check.Print();

    // RelaxationMethod relaxationMethodObject(3);
    // relaxationMethodObject.findAnswer(0.5, 100, 1e-10);

    return 0;
}



/*
3
2 0 -1 -3
-1 3 1 2
1 -1 4 4
*/

/*
4
4 -1 -6 0 2
-5 -4 10 8 21
0 9 4 -2 -12
1 0 -7 5 -6
*/ //ans is 3 -2 2 1