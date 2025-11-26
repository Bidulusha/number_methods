#include <iostream>
#include <iomanip>
#include <sstream>

#pragma once


enum matrix_features{
    WITH_RIGHT_PART,
    NO_RIGHT_PART,
    NO_INITIALIZE
};

class Matrix {
private:
    int size = -1;

    long double eps = 1e-10;

    bool isDiagonal = false; 
    bool hasBPart = true;
    bool isInitialized = false;

protected:
    long double ** matrixA;
    long double * matrixB;

    long double ** matrixASave;
    long double * matrixBSave;


public:
    //////////////////Constructors
    Matrix(long double ** matrixA, long double * matrixB, int size, int hasBPart = true){
        this->size = size;
        this->isDiagonal = false;
        this->hasBPart = hasBPart;
        
        // Создаем новые массивы и копируем данные
        this->matrixA = new long double*[size];
        this->matrixB = new long double[size];
        this->matrixASave = new long double*[size];
        this->matrixBSave = new long double[size];
        
        for (int i = 0; i < size; i++) {
            this->matrixA[i] = new long double[size];
            this->matrixASave[i] = new long double[size];
            this->matrixB[i] = matrixB[i];
            this->matrixBSave[i] = matrixB[i];
            
            for (int j = 0; j < size; j++) {
                this->matrixA[i][j] = matrixA[i][j];
                this->matrixASave[i][j] = matrixA[i][j];
            }
        }
    }
    
    Matrix(const Matrix& newMatrix) {
        size = newMatrix.size;
        isDiagonal = newMatrix.isDiagonal;
        hasBPart = newMatrix.hasBPart;

        matrixA = new long double*[size];
        matrixB = new long double[size];
        matrixASave = new long double*[size];
        matrixBSave = new long double[size];
        
        // Копируем данные
        for (int i = 0; i < size; i++) {
            matrixA[i] = new long double[size];
            matrixASave[i] = new long double[size];
            matrixB[i] = newMatrix.matrixB[i];
            matrixBSave[i] = newMatrix.matrixBSave[i];
            
            for (int j = 0; j < size; j++) {
                matrixA[i][j] = newMatrix.matrixA[i][j];
                matrixASave[i][j] = newMatrix.matrixASave[i][j];
            }
        }
    }

    Matrix(matrix_features feature = WITH_RIGHT_PART) {
        switch(feature){
            case WITH_RIGHT_PART:
                this->hasBPart = true;
                break;
            case NO_RIGHT_PART:
                this->hasBPart = false;
                break;
            case NO_INITIALIZE:
                return;
            }
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
    //Get element
    long double GetElement(int n, int m = -1){
        if (n == size) return matrixB[n];
        else return matrixA[n][m];
    }

    //Set and get eps
    void SetEpsilon(long double newEps) { eps = newEps; }
    long double GetEpsilon() { return eps; }

    //////////////////Functions

    ////////Work with matrix
    //To diagonal matrix
    void ToDiagonalMatrix(){
        long double coef = 1;

        for (int i = 0; i < size; i++){
            for (int j = i + 1; j < size; j++){
                coef = matrixA[j][i] / matrixA[i][i];

                matrixB[j] -= matrixB[i] * coef;
                SubtractRows(matrixA[j], matrixA[i], coef);
            }
            std::cout << "Iteration nubmer: " << i + 1 << std::endl;
            Print();
        }

        std::cout << "Revers steps" << std::endl;

        for (int i = size - 1; i > -1; i--){
            for(int j = i - 1; j > -1; j--){
                coef = matrixA[j][i] / matrixA[i][i];

                matrixB[j] -= matrixB[i] * coef;
                SubtractRows(matrixA[j], matrixA[i], coef);
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
    //Transposed matrix
    Matrix Transposed(){
        long double ** matrixA = new long double*[size];
        long double * matrixB = new long double[size];


        for(int i = 0; i < size; i++){
            matrixA[i] = new long double[size];
            for(int j = 0; j < size; j++){
                matrixA[i][j] = this-> matrixA[j][i];
            }
            matrixB[i] = 0;
        }
        return Matrix(matrixA, matrixB, size, false);
    }


    ////////Operators
    Matrix operator * (long double number){
        long double ** matrixA = new long double*[size];
        long double * matrixB = new long double[size];

        for (int i = 0; i < size; i++){
            matrixA[i] = new long double[size];
            for (int j = 0; j < size; j++){
                matrixA[i][j] = this->matrixA[i][j] * number;
            }
            matrixB[i] = this->matrixB[i] * number;
        }

        return Matrix(matrixA, matrixB, size, this->hasBPart);
    }

    Matrix operator * (const Matrix& matrixTo){
        if (size != matrixTo.size){
            std::cout << "Not allowed" << std::endl;
            return *this;
        }

        long double ** matrixA = new long double*[size];
        long double * matrixB = new long double[size];

        for (int i = 0; i < size; i++){
            matrixA[i] = new long double[size];
            for (int j = 0; j < size; j++){
                matrixA[i][j] = 0;
                for(int k = 0; k < size; k++){
                    matrixA[i][j] += this->matrixA[i][k] * matrixTo.matrixA[k][j];
                }
            }
        }
        return Matrix(matrixA, matrixB, size, matrixTo.hasBPart);
    }

    Matrix operator / (long double number){
        long double ** matrixA = new long double*[size];
        long double * matrixB = new long double[size];

        for (int i = 0; i < size; i++){
            matrixA[i] = new long double[size];
            for (int j = 0; j < size; j++){
                matrixA[i][j] = this->matrixA[i][j] / number;
            }
            matrixB[i] = this->matrixB[i] / number;
        }

        return Matrix(matrixA, matrixB, size, this->hasBPart); 
    }

    Matrix operator + (const Matrix& matrixTo){
        long double ** matrixA = new long double*[size];
        long double * matrixB = new long double[size];

        for (int i = 0; i < size; i++){
            matrixA[i] = new long double[size];
            for (int j = 0; j < size; j++){
                matrixA[i][j] = this->matrixA[i][j] + matrixTo.matrixA[i][j];
            }
            matrixB[i] = this->matrixB[i] + matrixTo.matrixB[i];
        }

        return Matrix(matrixA, matrixB, size, matrixTo.hasBPart);
    }

    Matrix operator - (const Matrix& matrixTo){
        long double ** matrixA = new long double*[size];
        long double * matrixB = new long double[size];

        for (int i = 0; i < size; i++){
            matrixA[i] = new long double[size];
            for (int j = 0; j < size; j++){
                matrixA[i][j] = this->matrixA[i][j] - matrixTo.matrixA[i][j];
            }
            matrixB[i] = this->matrixB[i] - matrixTo.matrixB[i];
        }

        return Matrix(matrixA, matrixB, size, matrixTo.hasBPart);
    }

    Matrix& operator = (const Matrix& matrixTo){
        if (this != &matrixTo) {
            if (size > 0) {
                for (int i = 0; i < size; i++){
                    delete[] matrixA[i];
                    delete[] matrixASave[i];
                }
                delete[] matrixA;
                delete[] matrixASave;
                delete[] matrixB;
                delete[] matrixBSave;
            }
            
            size = matrixTo.size;
            isDiagonal = matrixTo.isDiagonal;
            hasBPart = matrixTo.hasBPart;

            matrixA = new long double*[size];
            matrixB = new long double[size];
            matrixASave = new long double*[size];
            matrixBSave = new long double[size];
            
            for (int i = 0; i < size; i++) {
                matrixA[i] = new long double[size];
                matrixASave[i] = new long double[size];
                matrixB[i] = matrixTo.matrixB[i];
                matrixBSave[i] = matrixTo.matrixBSave[i];
                
                for (int j = 0; j < size; j++) {
                    matrixA[i][j] = matrixTo.matrixA[i][j];
                    matrixASave[i][j] = matrixTo.matrixASave[i][j];
                }
            }
        }
        return *this;
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
    void Print(int precision = 6){
        // Автоматически находим максимальную необходимую ширину
        int max_cell_width = 0;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                std::ostringstream oss;
                if (std::abs(matrixA[i][j]) < eps) {
                    oss << 0;
                } else {
                    oss << std::fixed << std::setprecision(precision) << matrixA[i][j];
                }
                max_cell_width = std::max(max_cell_width, (int)oss.str().length());
            }
            if (hasBPart) {
                std::ostringstream oss;
                if (std::abs(matrixB[i]) < eps) {
                    oss << 0;
                } else {
                    oss << std::fixed << std::setprecision(precision) << matrixB[i];
                }
                max_cell_width = std::max(max_cell_width, (int)oss.str().length());
            }
        }
        
        max_cell_width += 2;  // добавляем отступы
        
        std::cout << std::fixed << std::setprecision(precision);
        
        // Рассчитываем ширину
        int matrix_width = size * (max_cell_width + 1) - 1;
        int total_width = matrix_width + (hasBPart ? max_cell_width + 3 : 2);
        
        // Верхняя рамка
        std::cout << "┌" << std::string(total_width, ' ') << "┐" << std::endl;
        
        for (int i = 0; i < size; i++){
            std::cout << "│ ";
            for (int j = 0; j < size; j++){
                if (std::abs(matrixA[i][j]) < eps) 
                    std::cout << std::setw(max_cell_width) << 0;
                else 
                    std::cout << std::setw(max_cell_width) << matrixA[i][j];
                
                if (j < size - 1) std::cout << " ";
            }
            
            if (hasBPart) {
                std::cout << " │ ";
                if (std::abs(matrixB[i]) < eps) 
                    std::cout << std::setw(max_cell_width) << 0;
                else 
                    std::cout << std::setw(max_cell_width) << matrixB[i];
            }
            std::cout << " │" << std::endl;
        }
        
        // Нижняя рамка
        std::cout << "└" << std::string(total_width, ' ') << "┘" << std::endl;
        std::cout << std::defaultfloat;
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
            if (hasBPart){
                std::cin >> input;
                matrixB[i] = input;
                matrixBSave[i] = input;
            }
            else {
                matrixB[i] = 0;
                matrixBSave[i] = 0;       
            }
        }
        std::cout << "Matrix initialized!" << std::endl;
    }

private:
    ////////Work with matrix
    //subtract columns
    void SubtractRows(long double* columnFrom, long double* columnWhat, long double coef){
        for (int i = 0; i < size; i++){
            columnFrom[i] -= columnWhat[i] * coef;
        }
    }

};