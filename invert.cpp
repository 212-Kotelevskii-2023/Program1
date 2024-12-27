#include "invert.hpp"
#include "matrix.hpp"
#include <math.h>
#include <algorithm>

using namespace std;

int invert(double *a, double *a_inv, int n)
{
    int i, j, k;
    int max_ind;
    double value, max_elem;
    
    double eps = 1e-30;

    // заполняем a_inv единичной матрицей
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            a_inv[j+i*n] = 0;
        
    for (i = 0; i < n; ++i)
        a_inv[i+i*n] = 1;
    
    //основный цикл
    for (i = 0; i < n; ++i)
    {
        max_elem = fabs(a[i * n + i]);
        max_ind = i;
        
        for (j = i + 1; j < n; ++j)
        {
            if (fabs(a[j*n+i]) > max_elem)
            {
                max_elem = fabs(a[j*n+i]);
                max_ind = j;
            }           
        }
        
        
        if (fabs(max_elem) <= eps)
            return -1;
        
    
        if (max_ind != i)
        {
            for (j = 0; j < n; ++j)
            {
             
               swap(a[max_ind*n+j], a[i*n+j]);
               swap(a_inv[max_ind*n+j], a_inv[i*n+j]);
            }
        }

        value = 1.0 / a[i*n+i];
        
        for (j = 0; j < n; ++j)
        {
            a[i*n+j] *= value;
            a_inv[i*n+j] *= value;
        }

        for (j = i + 1; j < n; ++j)
        {
            value = a[j*n+i];
            
            for (k = 0; k < n; ++k)
            {
                a[j*n+k] -= a[i*n+k] * value;
                a_inv[j*n+k] -= a_inv[i*n+k] * value;
            }    
        }
    }

    // обратный ход
    for (k = 0; k < n; ++k) // выбор столбца
    {
        for (i = n-1; i >= 0; --i) // выбор строки
        {
            value = a_inv[i*n+k]; // зафиксировали элемент обратной

            for (j = i+1; j < n; ++j) // бежим
                value -= a[i*n+j] * a_inv[j*n+k];

            a_inv[i*n+k] = value;
        }
    }

    return 0;
}
