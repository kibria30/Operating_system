#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 

int main(){
    int pid, sum;
    pid = fork();
    int arr[] = {1,2,3,4,5,6,7,8,9};
    switch (pid){
        case 0: 
            sum = 0;
            for(int i=0; i<9; i++){
                if(arr[i]%2 == 1){
                    sum = sum + arr[i];
                }
            }
            printf("sum of odd number(child process): %d\n", sum);
            break;

        default:
            sum = 0;
            for(int i=0; i<9; i++){
                if(arr[i]%2 == 0){
                    sum = sum + arr[i];
                }
            }
            printf("sum of even number(parent process): %d\n", sum);
            break;
        case -1: 
            perror("fork");
            exit(1);
    }
    exit(0);
}