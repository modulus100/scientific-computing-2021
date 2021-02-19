#include <stdio.h>
#include <time.h>
#ifdef __APPLE__
#include <Accelerate/Accelerate.h>
#else
#include <cblas.h>
#endif

double random_in_range(double min, double max);
void print_matrix(double** matrix, int num_of_columns, int num_of_rows);

double **generate_matrix(int num_of_columns, int num_of_rows);
double **generate_empty_matrix(int num_of_columns, int num_of_rows);
double **generate_test_matrix(int num_of_columns, int num_of_rows);
double **matrix_multiplication(double** matrix1, double** matrix2, int num_of_columns, int num_of_rows);

void multiplication_example(int num_of_columns, int num_of_rows);
void multiplication_test();

int main()
{
    int i = 0;
    double A[6] = {1.0,2.0,1.0,-3.0,4.0,-1.0};
    double B[6] = {1.0,2.0,1.0,-3.0,4.0,-1.0};
    double C[9] = {.5,.5,.5,.5,.5,.5,.5,.5,.5};

    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,3,3,2,1,A, 3, B, 3,2,C,3);

//    for(i=0; i<9; i++)
//        printf("%lf ", C[i]);
//    printf("\n");

//    printf("random: %f", random_in_range(-2, 2));

//    multiplication_test();

    multiplication_example(100, 100);
//    multiplication_example(1000, 1000);
//    multiplication_example(5000, 5000);

    return 0;
}


void multiplication_example(int num_of_columns, int num_of_rows) {
    double** matrix_1 = generate_matrix(num_of_columns, num_of_rows);
    double** matrix_2 = generate_matrix(num_of_columns, num_of_rows);
    double** result = matrix_multiplication(matrix_1, matrix_2, num_of_columns, num_of_rows);

    free(matrix_1);
    free(matrix_2);
    free(result);
}

double **matrix_multiplication(double** matrix1, double** matrix2, int num_of_columns, int num_of_rows) {
    double** result = generate_empty_matrix(num_of_columns, num_of_rows);
    double execution_time;
    int i, j, k;
    clock_t begin = clock();

    for (i = 0; i < num_of_rows; i++) {
        for (j = 0; j < num_of_columns; j++) {
            for (k = 0; k < num_of_columns; k++) {
                *(*(result + i) + j) += *(*(matrix1 + i) + k) * *(*(matrix2 + k) + j);
            }
        }
    }

    clock_t end = clock();
    execution_time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%dx%d matrix multiplication time is %f seconds\n", num_of_columns, num_of_rows, execution_time);

    return result;
}

double **generate_matrix(int num_of_columns, int num_of_rows) {
    int i, j;
    double **matrix;

    matrix = malloc(num_of_rows * sizeof(double *));

    for (i = 0; i < num_of_columns; i++) {
        matrix[i] = malloc(num_of_columns * sizeof(double));

        for (j = 0; j < num_of_columns; j++) {
            *(*(matrix + i) + j) = random_in_range(-2, 2);
        }
    }

    return matrix;
}

double **generate_test_matrix(int num_of_columns, int num_of_rows) {
    int i, j;
    double **matrix;

    matrix = malloc(num_of_rows * sizeof(double *));

    for (i = 0; i < num_of_columns; i++) {
        matrix[i] = malloc(num_of_columns * sizeof(double));

        for (j = 0; j < num_of_columns; j++) {
            *(*(matrix + i) + j) = i + 1;
        }
    }

    return matrix;
}

void print_matrix(double** matrix, int num_of_columns, int num_of_rows) {
    int i, j;

    for (i = 0; i < num_of_rows; i++) {
        for (j = 0; j < num_of_columns; j++) {
            printf("array[%d][%d] = %f\n", i, j, *(*(matrix + i) + j));
        }
    }
}

double random_in_range(double min, double max) {
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

double **generate_empty_matrix(int num_of_columns, int num_of_rows) {
    double **matrix;
    int i;

    matrix = malloc(num_of_rows * sizeof(double *));

    for (i = 0; i < num_of_columns; i++) {
        matrix[i] = malloc(num_of_columns * sizeof(double));
    }

    return matrix;
}

void multiplication_test() {
    int num_of_columns = 3;
    int num_of_rows = 3;

    double** matrix_1 = generate_test_matrix(num_of_columns, num_of_rows);
    double** matrix_2 = generate_test_matrix(num_of_columns, num_of_rows);
    double execution_time;

    clock_t begin = clock();
    double** result = matrix_multiplication(matrix_1, matrix_2, num_of_columns, num_of_rows);
    clock_t end = clock();

    print_matrix(result, num_of_columns, num_of_rows);

    execution_time = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
    printf("%dx%d matrix multiplication time is %f milliseconds", num_of_columns, num_of_rows, execution_time);

    free(matrix_1);
    free(matrix_2);
    free(result);
}
