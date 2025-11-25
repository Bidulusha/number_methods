#include <iostream>
#include "matrix.hpp"

#pragma once

class CramersMatrix : public Matrix{
    bool variablesIsFound = false;

    long double determinantOfMatrix;
    long double * variables;

public:
    //////////////////Getters
    //Get determinant
    long double GetDeterminant(){
        return determinantOfMatrix;
    }

    //////////////////Constructors
    CramersMatrix() : Matrix(){
        determinantOfMatrix = FindDeterminant();
        variables = new long double[Size()];
    }

    //Destructor
    ~CramersMatrix(){
        delete variables;
    }

    //////////////////Functions
    //Find variables
    long double * FindVariables(){
        std::cout << variables[0] << std::endl;
        if (!variablesIsFound){
            for (int i = 0; i < Size(); i++){
                ChangeColumn(i);
                variables[i] = FindDeterminant() / determinantOfMatrix;
                std::cout << "x" << i << " = " << variables[i] << std::endl;
            }
            variablesIsFound = true;
        }
        else{
            for (int i = 0; i < Size(); i++){
                std::cout << "x" << i << " = " << variables[i] << std::endl;
            }
        }

        return variables; 
    }

    //Check answer
    void CheckAnswer(){
        long double answer;

        std::cout << "Check answer" << std::endl;

        if (!variablesIsFound) FindVariables();
        for (int i = 0; i < Size(); i++){
            answer = 0;
            for(int j = 0; j < Size(); j++){
                answer += matrixA[i][j] * variables[j];
            }
            std::cout << "row " << i + 1 << ": " << answer << " = " << matrixB[i] << std::endl;
        }
    }

private:
    //////////////////Functions
    // change column from matrixA to column from matrixB
    void ChangeColumn(int indexOfColumn){
        for (int i = 0; i < Size(); i++){
            matrixA[i][indexOfColumn] = matrixB[i];
        }
        std::cout << "Column changed!" << std::endl;
        Print();
    }
};