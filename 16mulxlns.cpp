#define xlns16_ideal
#include "xlns16.cpp"  

#include <iostream>
#include <vector>
#include <iomanip>

xlns16_float fp2xlns16_(float y) {
    xlns16_float z;
    z = y;  // Use the existing assignment operator
    return z;
}


//---------------------------------------------------------------------
std::vector<float> lnsMatrixMultiply(const float* matrixA, const float* matrixB,
                                       int rowsA, int colsA, int rowsB, int colsB) {

    int res_rows = rowsA;
    int res_cols = rowsB;

    // Convert FP input matrices to LNS arrays.
    std::vector<xlns16_float> A_LNS(rowsA * colsA);
    std::vector<xlns16_float> B_LNS(rowsB * colsB);
    for (int i = 0; i < rowsA * colsA; i++) {
        A_LNS[i] = matrixA[i];  // Automatic FP → LNS conversion.
    }
    for (int i = 0; i < rowsB * colsB; i++) {
        B_LNS[i] = matrixB[i];
    }

    std::vector<xlns16_float> result_LNS(rowsA * res_cols, 0.0f);


    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < res_cols; j++) {
            xlns16_float sum = 0.0f;
            for (int k = 0; k < colsA; k++) {
                sum = sum + A_LNS[i * colsA + k] * B_LNS[j * colsB + k];
            }
            result_LNS[i * res_cols + j] = sum;
        }
    }

    std::vector<float> result_FP(rowsA * res_cols);
    for (int i = 0; i < rowsA * res_cols; i++) {
        result_FP[i] = xlns16_2float(result_LNS[i]); 
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

    std::vector<float> result = lnsMatrixMultiply(matrixA, matrixB, rowsA, colsA, rowsB, colsB);


    std::cout << "16-bit FP matrix multiply using internal LNS computation:\n";
    for (int j = 0; j < rowsB; j++) {
        for (int i = 0; i < rowsA; i++) {
            std::cout << std::fixed << std::setprecision(2)
                      << result[i * rowsB + j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
