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
void print_process_maps(int arr[], int size , int * index, int h);
void merge_normal(int arr[] , int left , int middle , int right);
void merge_sort_normal(int arr[], int left , int right);
void mergeFork(int arr[] , int size , int write_fd_arr , int proc_pipe[] , int h);
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
    g_height = floor(log(g_max_process) / log(2)) + 1;
    g_size = numbers[0];
    int * nums = nums = (int *) malloc(sizeof(int)*numbers[0]); 
    for(i = 0 ; i < numbers[0] ; i++)
        nums[i] = numbers[i + 1];
    int * tree_arr = generate_arr_for_process(g_max_process , g_height);
    int tree_index = 0;
    printf("===Esquema de arbol===\n");
    print_header(tree_arr , nums, numbers[0]);
    printf("\n");
    printf("===Mapeos===\n");
    print_process_maps(nums, numbers[0] , &tree_index , 0);
    printf("===Procesamiento===\n");
    
    //make the pipes
    int process_count = 0;
    int fd_arr[2];
    int fd_proc[2];
    if(pipe(fd_arr) == -1){
        perror("Failed to create pipe");
        return -1;
    }
    if(pipe(fd_proc) == -1){
        perror("Failed to create pipe");
        return -1;
    }
    //write to pipes
    write(fd_arr[1] , nums, sizeof(int)*numbers[0]);
    write(fd_proc[1] , &process_count , sizeof(int));
    mergeFork(nums, numbers[0] , fd_arr[1] , fd_proc , 0);
    return 0;
}


/*mergeFork*/
void mergeFork(int arr[] , int size , int write_fd_arr , int proc_pipe[] , int h){
    int process_num;
    int act_p;
    int fd1[2];
    read(proc_pipe[0] , &process_num , sizeof(int));
    act_p = process_num;
    /*if(process_num < g_max_process){
        printf("Process N: %d\n" , process_num);
        print_array(arr, 0 , size -1 );   
        printf("\n"); 
    }else{
        printf("Process N: %d\n" , process_num);
    }*/
    if(h == g_height - 1 && process_num < g_max_process && size > 1){
        printf("Process %d: " , process_num);
        merge_sort_normal(arr, 0 , size -1);
        printf("lista ordenada: {");
        print_array(arr, 0 , size -1);    
        printf("}\n");
        write(write_fd_arr , arr , sizeof(int)*size);
        write(proc_pipe[1] , &process_num , sizeof(int));
        exit(0);
    }else if(h < g_height - 1){

        int leftSize, rightSize;
        pid_t leftChildPID , rightChildPID;
        int tmp =0;

        //make pipe
        if(pipe(fd1) == -1){
            perror("Failed to create pipe");
            exit(1);
        }
        //define size for children arrays
        if(size % 2 != 0){
            leftSize = size/2;
            rightSize = leftSize + 1;
        }else{
            leftSize = rightSize = size/2;
        }
        //define the children arrays
        int leftC_arr[leftSize];
        int rightC_arr[rightSize];

        //fork left and right
        if(!(leftChildPID = fork())){ //fork for left child
            process_num++; 
            write(proc_pipe[1] , &process_num , sizeof(int));
            copy(leftC_arr ,arr , leftSize);// copy for left child
            mergeFork(leftC_arr , leftSize , fd1[1] , proc_pipe , h +1);   
        }else{
            waitpid(leftChildPID , NULL , 0);
            read(proc_pipe[0], &tmp , sizeof(int));
        }

        if(leftChildPID > 0 && !(rightChildPID = fork())){ //fork for right child
            if(tmp > process_num)
                process_num = tmp;
            process_num++;
            write(proc_pipe[1] , &process_num , sizeof(int));
            copy(rightC_arr , arr + leftSize , rightSize);

            mergeFork(rightC_arr , rightSize , fd1[1], proc_pipe , h + 1);   
        }else if(leftChildPID > 0){
            waitpid(rightChildPID ,NULL , 0);
        }


        /*merge from parent branch*/
        if(leftChildPID != rightChildPID){
            int cmb_size = leftSize + rightSize;
            int combined[cmb_size];
            read(fd1[0] , &leftC_arr , sizeof(int)*leftSize);
            read(fd1[0] , &rightC_arr , sizeof(int)*rightSize);
            
            merge_sort_p(leftC_arr , rightC_arr , combined , leftSize , rightSize);
            if(act_p < g_max_process - 1){    
                printf("Proceso %d: lista izquierda {", act_p);
                print_array(leftC_arr , 0 , leftSize -1);
                printf("}, lista derecha {");
                print_array(rightC_arr , 0 , rightSize - 1);
                printf("}=> ");
                print_array(combined , 0 , size -1);
                printf("\n");
            }else{
                printf("Process %d: " , process_num);
                printf("lista ordenada: {");
                print_array(combined, 0 , size -1);    
                printf("}\n");
            }
            if(cmb_size < g_size){
                write(write_fd_arr , combined , sizeof(int)*cmb_size);
                exit(0);
            }
        }
    }else if(size == 1){
        write(write_fd_arr , arr, sizeof(int));
        write(proc_pipe[1] , &process_num , sizeof(int));
        exit(0);
    }else if(process_num >= g_max_process && size > 1 ){
        merge_sort_normal(arr , 0 , size -1);
        write(write_fd_arr , arr , sizeof(int)*size);
        write(proc_pipe[1] , &process_num , sizeof(int));
        exit(0);
    }
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


void print_process_maps(int arr[], int size , int * index, int h){
    if(*index < g_max_process && h < g_height){
        printf("Proceso %d: " , *index);
        print_array(arr , 0 , size - 1);
        printf("\n");
        int leftSize, rightSize;
        if(size % 2 != 0){
            leftSize = size/2;
            rightSize = leftSize + 1;
        }else
            leftSize = rightSize = size /2;
        
        int left_arr[leftSize];
        int right_arr[rightSize];
        copy(left_arr , arr , leftSize);
        copy(right_arr , arr + leftSize, rightSize);
        (*index)++;
        print_process_maps(left_arr , leftSize , index , h + 1 );
        print_process_maps(right_arr , rightSize , index , h + 1 );
    }
}


void merge_sort_normal(int arr[], int left , int right){
    if(left < right){
        int p = left + (right - left)/2;
        merge_sort_normal(arr , left , p);
        merge_sort_normal(arr , p + 1 , right); 
        merge_normal(arr , left , p , right);
    }
}


void merge_normal(int arr[] , int left , int middle , int right){
    int i,j,k;
    int n1 = middle - left + 1;
    int n2 = right - middle ;
    int L[n1] , R[n2];
    
    for(i = 0 ; i < n1 ; i++)
        L[i] = arr[left + i];
    for(j = 0 ; j < n2 ; j++)
        R[j] = arr[middle + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    while(i < n1 && j < n2){
        if(L[i] <= R[j] )
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];
    while(j < n2)
        arr[k++] = R[j++];


}
/*end of aux functions*/