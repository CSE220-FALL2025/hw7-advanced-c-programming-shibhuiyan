#include "hw7.h"
#include <stdio.h>
#include <string.h> 

///////////////////////
bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    // The function creates a new BST if the root is NULL.
    if (!root) { 
        bst_sf *newNode = malloc(sizeof(bst_sf)); 
        newNode->mat = mat; 

        return newNode;  //Return a pointer to the root of the new BST 
    }

    //if inserting matrix name comes before root's value's (a matrix) name 
    // then it should go to the left subtree 
    // binary trees are RECURSIVE 
    if ((mat-> name) < (root->mat->name)) { 
        root-> left_child = insert_bst_sf(mat, root->left_child); 
    } else 
        if ((mat->name) > (root->mat->name)) { 
            root->right_child = insert_bst_sf(mat, root->right_child); 
        }

    return root; // Return a pointer to the root of the updated BST
}
////////////////////

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    if (!root) { 
        return NULL; 
    } 

    while(root) { 
    // if the root node contains the matrix in search, return the root node matrix 
        if (root->mat->name == name) { 
            return root-> mat; 
        } else 
    // have to search left subtree if the matrix in search comes before root
            if (name < root->mat-> name) { 
                return find_bst_sf(name, root-> left_child);         
            } else 
    // have to search right subtree if the matrix in search comes before root
                if (name > root->mat-> name) { 
                    return find_bst_sf(name, root ->right_child); 
                }
    }   
}
////////////////////

void free_bst_sf(bst_sf *root) {
    if (!root) { 
        return; 
    }

    free_bst_sf(root->right_child); 
    free_bst_sf(root->left_child);   // bottoms up 

    free(root->mat); 
    free(root); 
}
////////////////////


///////////////////////////////////////////
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
//////////////////////////////////////////

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
            dotSum += mat1 ->values[(i * innerDimensions) +k] * mat2->values[(k * numCols) +j]; 
        }
        productValues[((i * numCols) + j)] = dotSum; 
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
//////////////////////////////////////////

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    int numRows = mat->num_rows; 
    int numCols = mat->num_cols; 
    
    int *transposedValues = malloc(sizeof(int) * numCols * numRows); 

    for(int i = 0; i < numRows; i++) { 
        for (int j = 0; j < numCols; j++) { 
            transposedValues[(numRows*j) + i] = mat->values[(numCols*i)+j]; 
        }
    } 

    matrix_sf *resultMat = malloc(sizeof(matrix_sf) + sizeof(int) * numCols*numRows); 
    resultMat -> num_cols = numRows; 
    resultMat->num_rows = numCols;  
    
    for (int i = 0; i < numCols*numRows; i++) { 
        resultMat->values[i] = transposedValues[i]; 
    }

    free(transposedValues); 
    return resultMat; 
}
//////////////////////////////////////////

matrix_sf* create_matrix_sf(char name, const char *expr) {
    int numRows, numCols, totalElements; 
  
// For example, for name = 'G', expr = "2 5 [ 8 4 9 1 13 ;-5 0 6 22 24;] "
    sscanf(expr, "%d %d", &numRows, &numCols); //extracts two integers which would signify the row and cols 

    matrix_sf *newMatrix = malloc(sizeof(matrix_sf) + sizeof(int) * numRows*numCols); 
    newMatrix->name = name;
    
    newMatrix->num_rows = numRows; 
    newMatrix->num_cols = numCols; 

    char *ptr = strchr(expr, '['); 
    for (int i = 0; i < totalElements; i++) { 
        while(isspace(*ptr)) { // this skips the spaces 
            ptr++; 
        }

        char *endPtr; 
        int currentExpValue = strtol(ptr,&endPtr, 10);  
        newMatrix->values[i] = currentExpValue; 
        ptr = endPtr; 

        if (*ptr == ';') { 
            ptr++; 
        }
    }
    return newMatrix; 
    // no free in this func b/c we need to put this into BST 
}
//////////////////////////////////////

int isPrecendent(char operator) { 
    int result; 
    if (operator == '+' || operator == '-') {
        result = -1;
    }

    if (operator == '*' || operator == '/') { 
        result = 0; 
    }

    if (operator == '\'') { 
        result = 1; 
    } 

    return result;

}

//////////////////

char* infix2postfix_sf(char *infix) {
    char result[strlen(infix)+ 1]; 
    char stack[100]; 
    int top, pop; 

    top = -1; 

    for (int i = 0; i < strlen(infix); i++) { 
        if (infix[i] == ' ') { 
        // skip space 
        } else { 
            if ( (infix[i] >= '0' && infix[i] <= '9') || (infix[i] >= 'a' && infix[i] <='z') 
                || (infix[i] >= 'A' && infix[i] <= 'a') ) { 
                    
                }
        }
    }

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
