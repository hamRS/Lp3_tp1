#include "tree_lib.h"
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define DELIMETER ","

/*global Variables*/
int g_max_process;
int g_height;
int g_size;
/*end of global variables*/

/*prototypes*/
int * get_int_argv(char c_nums[] , char * delimeter);
void generate_arr_for_process(int max_processes , int max_h, int arr[]);
int start_process(int * numbers);

void merge_sort_p(int first[] , int second[] , int combined[] ,int leftSize , int rightSize);
void copy(int * arr1 , int * arr2 , int size);
void print_array(int arr[] , int left , int right);
/*end of prototypes*/

int main(int argc , char * argv[]){
    if(argc != 3){
        fprintf(stderr , "Usage: %s <processes> <numbers>\n", argv[0]);
        return -1;
    }
    //global number of process
    g_max_process = atoi(argv[1]);
    int * numbers = get_int_argv(argv[2] , DELIMETER);
    if(g_max_process % 2 == 0){ //process number has to form left and right childs
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
    int h = floor(log(g_max_process) / log(2)) + 1;
    int process_count = 0;
    int * nums;
    nums = (int *) malloc(sizeof(int)*numbers[i]); 
    for(i = 0 ; i < numbers[0] ; i++)
        nums[i] = numbers[i + 1];
    int tree_arr[g_max_process];
    generate_arr_for_process(g_max_process , h, tree_arr);
    print_array(tree_arr , 0 , g_max_process -1);
    printf("/n");
    return 0;
}
/*aux functions*/
void print_array(int arr[] , int left , int right){
    int i;
    for(i = left; i <= right ; i++)
        printf("%d,", arr[i]);
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


void generate_arr_for_process(int max_processes , int max_h, int arr[]){
    struct node * root = NULL;
    int index = 0;
    int p_count = 0;
    createTree(&root , max_processes , &p_count , 0 , max_h );
    levelOrder(root , arr , &index, max_processes , 0);
    free(root);
}
/*end of aux functions*/