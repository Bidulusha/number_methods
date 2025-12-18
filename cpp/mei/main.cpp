#include <iostream>
#include <iomanip>

using ll = long long;
using ld = long double;

long double *getMatrix(ll n){
    long double* matrix = new long double[n + 1];
    for (ll i = 0; i < n; i++){
        for (ll j = 0; j < n + 1; j++){
            std::cin >> matrix[j];
        }
    } 
    return matrix;
}

void printMatrix(const ld& matrix, ll size){
    
}

int main(){
    ll n;
    
    std::cout << "Get matrix from keyboard input" << std::endl;
    std::cout << "Count of elements in coefficients matrix: ";
    std::cin >> n;
    
    long double * matrix = getMatrix(n);
    

    return 0;
}