#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define DELIMETER ","

/*global Variables*/
int * nums_global;
int prN;
int max_processes;
/*end of global variables*/

/*prototypes*/
int * get_int_argv(char c_nums[] , char * delimeter);
int start_process(int * numbers);
void print_header(int n);
void print_arrLevel(int level, int counter, int n);
void print_treeMap(int n);
void print_array(int left , int right);
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
    int left,right;

    printf("===Esquema de arbol===\n");
    //print nums mapping 
    print_treeMap(prN, numbers[0]);
    printf("===mapeos===\n");
    merge_sort_process(0, numbers[0] - 1, 0,&process_count, prN , h);
    return 0;
}
void merge_sort_process(pid_t chidlPID , int heigth, int left , int right , int h_max, int flag){
    
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
    printf("\n");
}

void print_treeMap(int prN , int n){
    print_header(prN , n);
}


void print_header(int prN , int n){
    int pr_count = 0;
    int i,j;
    int level = 0;
    int counter = 0;
    while(pr_count < prN){
        counter = 0;
        for(i = 0 ; i < pow(2 , level) ; i++ ){
            for(j = n/4  ; j >= level ; j--) //print tabs
                printf("\t");
            printf("Process %d" , pr_count++);
            if(pr_count >= prN) break;
            counter++;
        }
        printf("\n");
        print_arrLevel(level, counter , pr_count , n);
        printf("\n");
        level++;
    }
}

void print_arrLevel( int level, int counter , int prN , int n){
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
            printf("%d," , nums_global[i]);
        left = i;
        right += n/pow(2 , level);
        if(right >= n && left < n)
            right = n - 1;
        count++;
    }
}
