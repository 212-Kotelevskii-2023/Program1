#include <stdio.h>
#include <time.h>
#include <math.h>
#include "matrix.hpp"
#include "invert.hpp"

int main(int argc, char **argv)
{
    int n, m, s;
    double *a;
    double *a_inv;
    FILE* fin = nullptr;
    clock_t t;
    double r = 0;
    int flag;

    if (argc < 4)
    {
        printf("Wrong input. Correct input:\n./a.out n m s *filename (if s == 0)\n");
        return -1;
    }

    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1 || sscanf(argv[3], "%d", &s) != 1)
    {
        printf("Input data is incorrect.\n");
        return -1;
    }

    if ((s == 0 && argc != 5) || (s != 0 && argc != 4))
    {
        printf("Input data is incorrect.\n");
        return -1;
    }

    if (n < 0 || m < 0 || m > n || s < 0 || s > 4)
    {
        printf("Data is incorrect.\n");
        return -1;
    }

    if (s == 0)
    {
        fin = fopen(argv[4], "r");

        if (!fin)
        {
            printf("File unfinded.\n");
            fclose(fin);
            return -2;
        }
    }

    a = new double [n*n]; //начальная матрица
    a_inv = new double [n*n]; //обратная матрица

    if (!(a && a_inv))
    {
        printf("Bad memory.\n");

        if (s == 0)
            fclose(fin);

        delete []a;
        delete []a_inv;

        return -2;
    }

    flag = enter_matrix(a, n, s, fin);

    if (flag < 0)
    {
        printf("Wrong matrix.\n");

        if (s == 0)
            fclose(fin);

        delete []a;
        delete []a_inv;

        return -2;
    }

    printf("Initial matrix:\n");
    print_matrix(a, n, m);

    t = clock();
    flag = invert(a, a_inv, n);
    t = clock() - t;

    if (flag == 0)
    {
        printf("\nInvert matrix:\n");
        print_matrix(a_inv, n, m);

        if (s == 0)
            fseek(fin, 0, SEEK_SET);

        flag = enter_matrix(a, n, s, fin);

        r = norm(a, a_inv, n);

        printf ("Norm = %e Time = %.2f S = %d N = %d\n",
                r, 1.0*t/CLOCKS_PER_SEC, s, n);
    }
    else
    {
        printf("Matrix is singular.\n");

        if (s == 0)
            fclose(fin);

        delete []a;
        delete []a_inv;

        return -1;
    }

    if (s == 0)
        fclose(fin);

    delete []a;
    delete []a_inv;

    return 0;
}
