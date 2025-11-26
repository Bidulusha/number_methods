#include <iostream>
#include "matrix.hpp"

#pragma once

class InvertibleMatrix{
private:
    Matrix _matrix = Matrix(NO_INITIALIZE);
    Matrix x0 = Matrix(NO_INITIALIZE);
    long double norm1 = 0;
    long double normInf = 0;

public:
    //////////Constructors
    InvertibleMatrix(const Matrix& newMatrix){
        _matrix = newMatrix;
        norm1 = findNorm1();
        normInf = findNormInf();
        x0 = findX0();
    }

    InvertibleMatrix() : InvertibleMatrix(Matrix(NO_RIGHT_PART)) {};

    ///////////Getters and setters
    Matrix matrix(){
        return _matrix;
    }


    ///////////Functions
    //find inverse _matrix
    Matrix findInverseMatrix(long double iterations){
        Matrix xk = x0;
        for(int i = 0; i < iterations; i++){
            xk = xk * 2 - xk * _matrix * xk;
        }
        return xk;
    }

protected:
    ///////////Functions
    //find norm 1
    long double findNorm1(){ //Columns
        long double norm = 0, temp = 0;
        for(int i = 0; i < _matrix.Size(); i++){
            temp = 0;
            for (int j = 0; j< _matrix.Size(); j++){
                temp += std::abs(_matrix.GetElement(j, i));
            }
            norm = temp > norm? temp : norm;
        }
        return norm;
    }

    //find norm infinity
    long double findNormInf(){ //Rows
        long double norm = 0, temp = 0;
        for(int i = 0; i < _matrix.Size(); i++){
            temp = 0;
            for (int j = 0; j< _matrix.Size(); j++){
                temp += std::abs(_matrix.GetElement(i, j));
            }
            norm = temp > norm? temp : norm;
        }
        return norm;
    }

    //find X0
    Matrix findX0(){
        return _matrix.Transposed() / (norm1 * normInf); 
    }
};