#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "tree_lib.h"
#define DELIMETER ","

/*global Variables*/
int g_max_process = MAX_PROCESS;
int g_height;
int g_size;
/*end of global variables*/

/*prototypes*/
int * get_int_argv(char c_nums[] , char * delimeter);
int start_process(int * numbers);
void print_array(int left , int right);

void merge_sort_p(int first[] , int second[] , int combined[] ,int leftSize , int rightSize);
void copy(int * arr1 , int * arr2 , int size);
/*end of prototypes*/

int main(int argc , char * argv[]){
    if(argc != 3){
        fprintf(stderr , "Usage: %s <processes> <numbers>\n", argv[0]);
        return -1;
    }
    //global number of process
    max_processes = atoi(argv[1]);
    prN = 0;
    int * numbers = get_int_argv(argv[2] , DELIMETER);
    if(numbers[0] % 2 == 0){ //process number has to form left and right childs
        perror("No se puede dividir el array de forma correcta");
        return -1;
    }

    if(numbers != NULL && numbers[0] > 1){
        start_process(numbers);
    }else{
        printf("===esquema de arbol===\n\t\tproceso 0\n");
        printf("\t\t\t%d\n" , numbers[1]);
        printf("===mapeos===\n proceso 0: %d\n" , numbers[1]);
        printf("===procesamiento===\n proceso 0: %d\n" , numbers[1]);
        printf("---------------------\n");
    }
    free(numbers);
    free(nums_global);
    return 0;
}

/*main functions*/
int * get_int_argv(char c_nums[] , char * delimeter){
    if(c_nums == NULL || strlen(c_nums) == 0)
        return NULL;
    if(strlen(c_nums) == 1){
        int * u = (int *) malloc(sizeof(int));
        u[0]= atoi(c_nums);
        return u;
    }
    int n = (strlen(c_nums) - 1)/2  + 1;
    int * numbers = (int *) malloc(sizeof(int) * (n+1));
    char * token = strtok(c_nums , delimeter);
    int i =1;
    while(token != NULL){
        numbers[i++] = atoi(token);
        token = strtok(NULL , delimeter);
    }
    numbers[0] = i - 1;
    return numbers;
}

int start_process(int * numbers){
    int i,j;
    int h = floor(log(prN) / log(2)) + 1;
    int process_count = 0;
    nums_global = (int *) malloc(sizeof(int)*numbers[i]); 
    for(i = 0 ; i < numbers[0] ; i++)
        nums_global[i] = numbers[i + 1];
       
    return 0;
}

void merge_sort(int left , int right){
    if(left < right){
        int p = left + (right - left)/2;
        merge_sort(left , p);
        merge_sort(p + 1 , right); 
        merge(left , p , right);
    }
}

void merge(int left , int middle , int right){
    int i,j,k;
    int n1 = middle - left + 1;
    int n2 = right - middle ;
    int L[n1] , R[n2];
    
    for(i = 0 ; i < n1 ; i++)
        L[i] = nums_global[left + i];
    for(j = 0 ; j < n2 ; j++)
        R[j] = nums_global[middle + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    while(i < n1 && j < n2){
        if(L[i] <= R[j] )
            nums_global[k++] = L[i++];
        else
            nums_global[k++] = R[j++];
    }

    while(i < n1)
        nums_global[k++] = L[i++];
    while(j < n2)
        nums_global[k++] = R[j++];


}
void print_array( int left , int right){
    int i;
    for(int i = left; i <= right ; i++)
        printf("%d," , nums_global[i]);
}

void merge_sort_p(int first[] , int second[] , int combined[] ,int leftSize , int rightSize){
    int i,j,k;
    j = i = k = 0;
    while(j < rightSize && i < leftSize){
        if(first[i] < second[j])
            combined[k++] = first[i++];
        else
            combined[k++] = second[j++];
    }
    while(i < leftSize)
        combined[k++] = first[i++];
    while(j < rightSize)
        combined[k++] = second[j++];
}   
void copy(int * arr1 , int * arr2 , int size){
    int i;
    for(i = 0 ; i < size ; i++)
        arr1[i] = *(arr2 + i);
}


/*end of aux functions*/