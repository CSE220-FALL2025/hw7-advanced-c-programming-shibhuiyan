#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    return NULL;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    return NULL;
}

void free_bst_sf(bst_sf *root) {
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    int totalElements = mat1 -> num_cols * mat1 ->num_rows; 
    int *sumValues = malloc(sizeof(int)*totalElements); 

    // adds the elements from m1 w/ m2 together 
    for (int i = 0; i < totalElements; i++) { 
        sumValues[i] = mat1 -> values[i] + mat2 -> values[i]; 
    }

    matrix_sf *resultMat = malloc(sizeof(matrix_sf) + sizeof(int) * totalElements); 
    resultMat -> num_cols = mat2 -> num_cols; 
    resultMat -> num_rows = mat1 -> num_rows; //already assuming they have the same dimensons so it doesnt matter which we call

    for (int i = 0; i < totalElements; i++) { 
        resultMat -> values[i] = sumValues[i]; 
    }
    free(sumValues);
    return resultMat;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
   int numRows = mat1 -> num_rows; 
   int numCols = mat2 -> num_cols; 
   // mat1 cols and mat2 rows should be the same to carry out matrix multiplication 
   int innerDimensions = mat2 -> num_rows; 

   int *productValues = malloc(sizeof(int) * numRows*numCols);
   
   for (int i = 0; i < numRows; i++) { 
    for (int j = 0; j < numCols; j++) { 
        int dotSum = 0; 
        for (int k = 0; k < innerDimensions; k++) { 
            // pretending its like 1D array 
            dotSum += mat1 ->values[i * innerDimensions+k] * mat2->values[k * numCols+j]; 
        }
        productValues = [row*numCols+j] = dotSum; 
    }
   }

   matrix_sf *resultMat = malloc(sizeof(matrix_sf) + sizeof(int) * numCols*numRows); 
   resultMat->num_rows = numRows; 
   resultMat->num_cols = numCols; 

   for (int i = 0; i < numCols*numRows; i++) { 
    resultMat->values[i] = productValues[i]; 
   }

   free(productValues); 
   return resultMat; 
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    return NULL;
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    return NULL;
}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
