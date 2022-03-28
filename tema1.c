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
int * generate_arr_for_process(int max_processes , int max_h);
int start_process(int * numbers);

void merge_sort_p(int first[] , int second[] , int combined[] ,int leftSize , int rightSize);
void copy(int * arr1 , int * arr2 , int size);
void print_array(int arr[] , int left , int right);
void print_arrLevel( int level, int counter , int prN , int n, int nums[]);
void print_header(int proc_pattern[], int nums[] , int n);
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
    int * nums = nums = (int *) malloc(sizeof(int)*numbers[0]); 
    for(i = 0 ; i < numbers[0] ; i++)
        nums[i] = numbers[i + 1];
    int * tree_arr = generate_arr_for_process(g_max_process , h);
    printf("===Esquema de arbol===\n");
    print_header(tree_arr , nums, numbers[0]);
    printf("\n");
    printf("===Mapeos===\n");
    return 0;
}
/*end of main functions*/

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


int * generate_arr_for_process(int max_processes , int max_h){
    struct node * root = NULL;
    int index = 0;
    int p_count = 0;
    int * arr = (int *) malloc(sizeof(int)*max_processes);
    createTree(&root , max_processes , &p_count , 0 , max_h );
    levelOrder(root , &arr , &index, max_processes , max_h);
    free(root);
    return arr;
}


void print_header(int proc_pattern[], int nums[] , int n){
    int index = 0;
    int i,j;
    int level = 0;
    int counter = 0;
    while(index < g_max_process){
        counter = 0;
        for(i = 0 ; i < pow(2 , level) ; i++ ){
            for(j = n/4  ; j >= level ; j--) //print tabs
                printf("\t");
            printf("Process %d" , proc_pattern[index++]);
            if(index >= g_max_process) break;
            counter++;
        }
        printf("\n");
        print_arrLevel(level, counter , index, n , nums);
        printf("\n");
        level++;
    }
}

void print_arrLevel( int level, int counter , int prN , int n, int nums[]){
    int right = n/pow(2 , level) - 1;
    int left = 0;
    int i;
    int count = 0;

    while(right < n && count <= counter){
        //print tabs
        for(i = n/4; i >= level ; i--)
            printf("\t");
        //print arr
        for(i = left ; i <= right ; i++)
            printf("%d," , nums[i]);
        left = i;
        right += n/pow(2 , level);
        if(right >= n && left < n)
            right = n - 1;
        count++;
    }
}
/*end of aux functions*/