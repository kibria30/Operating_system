#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 

int A[3][3] = {{12, 8, 4}, {3, 17, 14}, {9, 8, 10}};
int B[3][3] = {{5, 19, 3}, {6, 15, 9}, {7, 8, 16}};
int R[3][3];

void multRow(int row){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            R[row][i] += A[row][j]*B[j][i];
        }
    }
}

void printMatrix(int X[3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d ", X[i][j]);
        }
        printf("\n");
    }
}

void printRow(int row){
    for(int i=0; i<3; i++){
        printf("%d ", R[row][i]);
    }
    printf("\n");
}

int main(){
    int pid;

    //multRow(0);
    //printMatrix(A);
    printf("\n");
    //printMatrix(B);
    printf("\n");
    //printMatrix(R);

    // for(int i = 1; i<3; i++){
    //     pid = fork();
    //     if(pid == 0){
    //         printf("Working in child: %d\n", i);
    //         multRow(i);
    //     }
    // }

    for(int i = 0; i<3; i++){
        pid = fork();
        if(pid == 0){
            printf("Working in child: %d\n", i);
            multRow(i);
            printRow(i);
            break;
        }
    }


    
    //printMatrix(R);
}