#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>

double f (int s, int n, int i, int j);
int enter_matrix(double *a, int n, int s, FILE* fin);
void print_matrix (double *a, int n, int m);
double norm(double *a, double *a_inv, int n);

#endif /* matrix_hpp */
