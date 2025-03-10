#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    // Define dimensions.
    const int rows_A = 4, cols_A = 2;
    const int rows_B = 3, cols_B = 2; //  we will transpose it.

    float matrix_A[rows_A * cols_A] = {
         2, 8,
         5, 1,
         4, 2,
         8, 6
    };

    float matrix_B[rows_B * cols_B] = {
        10, 5,
         9, 9,
         5, 4
    };

    const int res_rows = rows_A;   // 4
    const int res_cols = rows_B;   // 3
    std::vector<float> result(res_rows * res_cols, 0.0f);

    
  
    for (int i = 0; i < res_rows; ++i) {
        for (int j = 0; j < res_cols; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < cols_A; ++k) {
                sum += matrix_A[i * cols_A + k] * matrix_B[j * cols_B + k];
            }
            result[i * res_cols + j] = sum;
        }
    }

 
    cout << "32-bit FP matrix multiply :" << std::endl;
    for (int j = 0; j < res_cols; ++j) { 
        for (int i = 0; i < res_rows; ++i) {
            cout << std::fixed << std::setprecision(2) 
                      << result[i * res_cols + j] << " ";
        }
        cout <<endl;
    }
    
    return 0;
}
