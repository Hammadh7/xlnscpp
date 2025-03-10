#define xlns32_ideal
#include "xlns32.cpp" 

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

xlns32_float fp2xlns32_(float y) {
    xlns32_float z;
    z = y; 
    return z;
}

vector<float> lnsMatrixMultiply(const float* matrixA, const float* matrixB,
                                int rowsA, int colsA, int rowsB, int colsB) {
    int res_rows = rowsA;
    int res_cols = rowsB;

    vector<xlns32_float> A_LNS(rowsA * colsA);
    vector<xlns32_float> B_LNS(rowsB * colsB);
    for (int i = 0; i < rowsA * colsA; i++) {
        A_LNS[i] = matrixA[i]; 
    }
    for (int i = 0; i < rowsB * colsB; i++) {
        B_LNS[i] = matrixB[i];
    }

    vector<xlns32_float> result_LNS(rowsA * res_cols, 0.0f);

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < res_cols; j++) {
            xlns32_float sum = 0.0f;
            for (int k = 0; k < colsA; k++) {
                sum = sum + A_LNS[i * colsA + k] * B_LNS[j * colsB + k];
            }
            result_LNS[i * res_cols + j] = sum;
        }
    }

    vector<float> result_FP(rowsA * res_cols);
    for (int i = 0; i < rowsA * res_cols; i++) {
        result_FP[i] = xlns32_2float(result_LNS[i]); 
    }
    return result_FP;
}

int main() {
    const int rowsA = 4, colsA = 2;
    const int rowsB = 3, colsB = 2;

    float matrixA[rowsA * colsA] = {
        2, 8,
        5, 1,
        4, 2,
        8, 6
    };

    float matrixB[rowsB * colsB] = {
        10, 5,
        9, 9,
        5, 4
    };

    vector<float> result = lnsMatrixMultiply(matrixA, matrixB, rowsA, colsA, rowsB, colsB);

    cout << "32-bit FP matrix multiply using internal LNS computation (transposed result):\n";
    for (int j = 0; j < rowsB; j++) {
        for (int i = 0; i < rowsA; i++) {
            cout << fixed << setprecision(2)
                 << result[i * rowsB + j] << " ";
        }
        cout << "\n";
    }

    return 0;
}