#include "matrix.hpp"
#include <stdio.h>
#include <math.h>

double f (int s, int n, int i, int j) {
    switch (s) {
        case 1:
            return n - fmax(i, j) + 1;
        case 2:
            return fmax(i, j);
        case 3:
            return fabs(i - j);
        case 4:
            return 1.0 / (i + j + 1);
        default:
            return -1;
    }
}

int enter_matrix(double *a, int n, int s, FILE* fin) {
    int i, j;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (s == 0) {
                if (fscanf(fin, "%lf", &a[i * n + j]) != 1)
                    return -1;
            }
            else {
                a[i*n+j] = f(s, n, i, j);
            }
        }
    }

    return 0;
}

void print_matrix(double* a, int n, int m) {
    m > n ? m = n : m = m;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%10.3e ", a[i * n + j]);
        }
        printf("\n");
    }
}

double norm(double* a, double* a_inv, int n)
{
    int i, j, k;
    double temp, sum = 0.0, max = 0.0;
        
    for (i = 0; i < n; ++i)
    {
        sum = 0.0;
        
        for (j = 0; j < n; ++j)
        {
            temp = 0.0;
            
            for (k = 0; k < n; ++k)
                temp += a[i*n+k] * a_inv[k*n+j];
            
            if (i == j)
                temp -= 1.0;
            
            sum += fabs(temp);
        }
        
        if (sum > max)
            max = sum;
    }
    
    return max;
}

