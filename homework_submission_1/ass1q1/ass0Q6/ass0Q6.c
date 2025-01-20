#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void print_to_file(int n, double **A, int format_flag);

int main() {
    int n;

    // Open the input file
    FILE *input_file = fopen("input.in", "r");
    if (input_file == NULL) {
        printf("Error: Could not open file 'input.in'\n");
        return 1;
    }

    // Read n from the file
    if (fscanf(input_file, "%d", &n) != 1) {
        printf("Error: Invalid input format in 'input.in'\n");
        fclose(input_file);
        return 1;
    }
    fclose(input_file);

    // Dynamically allocate a 2D array
    double **A = (double **)malloc(n * sizeof(double *));
    if (A == NULL) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        if (A[i] == NULL) {
            printf("Error: Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                free(A[j]);
            }
            free(A);
            return 1;
        }
    }

    // Fill the array with A[i][j] = i + j
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
        }
    }

    // Call the function to write the array to file
    int format_flag = 1 ; // Change to 1 for binary format
    print_to_file(n, A, format_flag);

    // Free the allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}

// Function to write the array to a file
void print_to_file(int n, double **A, int format_flag) {
    char filename[50];
    snprintf(filename, sizeof(filename), "array_%06d_%s.out", n, format_flag == 0 ? "asc" : "bin");

    FILE *file = fopen(filename, format_flag == 0 ? "w" : "wb");
    if (file == NULL) {
        printf("Error: Could not open file '%s' for writing\n", filename);
        return;
    }

    if (format_flag == 0) {
        // Write in ASCII format
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(file, "%.15e ", A[i][j]); // 15-decimal places precision
            }
            fprintf(file, "\n");
        }
    } else {
        // Write in binary format
        for (int i = 0; i < n; i++) {
            fwrite(A[i], sizeof(double), n, file);
        }
    }

    fclose(file);
    printf("Array written to '%s'\n", filename);
}
