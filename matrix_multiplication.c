#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 4

// Matrix dimensions (change as needed)
int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

// Number of threads (equal to the number of rows in matrix A)
pthread_t threads[MAX];

// Struct to pass multiple arguments to thread function
typedef struct {
    int row;
} thread_data;

// Thread function to perform matrix multiplication for a single row
void* multiply(void* arg) {
    thread_data* data = (thread_data*)arg;
    int row = data->row;

    for (int i = 0; i < MAX; i++) {
        C[row][i] = 0;
        for (int j = 0; j < MAX; j++) {
            C[row][i] += A[row][j] * B[j][i];
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Initialize matrices A and B
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Print matrix A
    printf("Matrix A:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    // Print matrix B
    printf("Matrix B:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    // Create threads to perform multiplication for each row
    for (int i = 0; i < MAX; i++) {
        thread_data* data = (thread_data*)malloc(sizeof(thread_data));
        data->row = i;
        pthread_create(&threads[i], NULL, multiply, (void*)data);
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result matrix C
    printf("Resultant Matrix C (A * B):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
