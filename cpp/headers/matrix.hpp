#include <iostream>
#pragma once

class Matrix {
private:
    int size = -1;
    bool isDiagonal = false; 


protected:
    long double ** matrixA;
    long double * matrixB;

    long double ** matrixASave;
    long double * matrixBSave;


public:
    //////////////////Constructors
    Matrix(long double ** matrixA, long double * matrixB){
        this->matrixA = matrixA;
        this->matrixB = matrixB;
    }
    
    Matrix() {
        InitializeMatrix();
    }

    ////////Destructor
    ~Matrix(){
        if (size > 0) {
            for (int i = 0; i < size; i++){
                delete[] matrixA[i];
                delete[] matrixASave[i];
            }
        }
        delete[] matrixA;
        delete[] matrixASave;
        delete[] matrixB;
        delete[] matrixBSave;
        }

    //////////////////Getters
    //Get size
    int Size(){
        return size;
    }
    //Get isDiagonal
    bool IsDiagonal(){
        return isDiagonal;
    }

    //////////////////Functions

    ////////Work with matrix
    //To diagonal matrix
    void ToDiagonalMatrix(){
        long double coef = 1;

        for (int i = 0; i < size; i++){
            for (int j = i + 1; j < size; j++){
                coef = matrixA[j][i] / matrixA[i][i];

                matrixB[j] -= matrixB[i] * coef;
                SubtractColumns(matrixA[j], matrixA[i], coef);
            }
            std::cout << "Iteration nubmer: " << i + 1 << std::endl;
            Print();
        }

        std::cout << "Revers steps" << std::endl;

        for (int i = size - 1; i > -1; i--){
            for(int j = i - 1; j > -1; j--){
                coef = matrixA[j][i] / matrixA[i][i];

                matrixB[j] -= matrixB[i] * coef;
                SubtractColumns(matrixA[j], matrixA[i], coef);
            }
            std::cout << "Iteration nubmer: " << size - i << std::endl;
            Print();
        }

        isDiagonal = true;
    }

    //Find determinant
    long double FindDeterminant(){
        long double determinant = 1;
        if(isDiagonal){
            for (int i = 0; i < size; i++){
                determinant *= matrixA[i][i];
            }
        }
        else{
            std::cout << "make diagonal matrix" << std::endl;
            ToDiagonalMatrix();
            for (int i = 0; i < size; i++){
                determinant *= matrixA[i][i];
            }
            ResetMatrix();
        }

        return determinant; 
    }
    


    ////////Work with memory
    //Reset matrix
    void ResetMatrix(){
        if (size == -1){
            std::cout << "Where is no elements!" << std::endl;
            return;
        }

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                matrixA[i][j] = matrixASave[i][j];
            }
        }
        for(int i = 0; i < size; i++){
            matrixB[i] = matrixBSave[i];
        }

        std::cout << "Matrix reset!" << std::endl;
        isDiagonal = false;
    }

    //Print
    void Print(){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                std::cout << matrixA[i][j] << " ";
            }
            std::cout << matrixB[i] << std::endl;
        }
    }

protected:
    ////////Initialize matrix
    void InitializeMatrix(){
        long double input;
        std::cin >> size;

        matrixA = new long double*[size];
        matrixB = new long double[size];

        matrixASave = new long double*[size];
        matrixBSave = new long double[size];

        for (int i = 0; i < size; i++){
            matrixA[i] = new long double[size];
            matrixASave[i] = new long double[size];

            for(int j = 0; j < size; j++){
                std::cin >> input;

                matrixA[i][j] = input;
                matrixASave[i][j] = input;
            }
            std::cin >> input;

            matrixB[i] = input;
            matrixBSave[i] = input;
        }

        std::cout << "Matrix initialized!" << std::endl;
    }

private:
    ////////Work with matrix
    //subtract columns
    void SubtractColumns(long double* columnFrom, long double* columnWhat, long double coef){
        for (int i = 0; i < size; i++){
            columnFrom[i] -= columnWhat[i] * coef;
        }
    }

};