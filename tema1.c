#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define DELIMETER ","

/*prototypes*/
int * get_int_argv(char c_nums[] , char * delimeter);
int start_process(int prN , int * numbers);
void print_header(int arr[] , int prN , int n);
void print_arrLevel(int arr[], int level, int counter , int prN , int n);
void print_treeMap(int arr[], int prN , int n);
/*end of prototypes*/

int main(int argc , char * argv[]){
    if(argc != 3){
        fprintf(stderr , "Usage: %s <processes> <numbers>\n", argv[0]);
        return -1;
    }
    int nbr_processes = atoi(argv[1]);
    int * numbers = get_int_argv(argv[2] , DELIMETER);
    printf("%d\n" , numbers[0]);
    if(numbers != NULL && numbers[0] > 1){
        start_process(nbr_processes , numbers);
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



int start_process(int prN , int * numbers){
    int i,j;
    int nums[numbers[0]]; ///nums to sort
    for(i = 0 ; i < numbers[0] ; i++)
        nums[i] = numbers[i + 1];
    pid_t childPID;
    int left,right;
    //print nums mapping 
    print_treeMap(nums, prN, numbers[0]);
    return 0;
}


void print_treeMap(int arr[], int prN , int n){
    print_header(arr , prN , n);
}


void print_header(int arr[] , int prN , int n){
    int pr_count = 0;
    int i,j;
    int level = 0;
    int counter = 0;
    while(pr_count < prN){
        counter = 0;
        for(i = 0 ; i < pow(2 , level) ; i++ ){
            for(j = n/4  ; j >= level ; j--)
                printf("\t");
            printf("Process %d" , pr_count++);
            if(pr_count >= prN) break;
            counter++;
        }
        printf("\n");
        print_arrLevel(arr,level, counter , pr_count , n);
        printf("\n");
        level++;
    }
}

void print_arrLevel(int arr[], int level, int counter , int prN , int n){
    int right = n/pow(2 , level) - 1;
    int left = 0;
    int i;
    int count = 0;

    while(right < n && count <= counter){
        //print tabs
        for(i = n/4 ; i >= level ; i--)
            printf("\t");
        //print arr
        for(i = left ; i <= right ; i++)
            printf("%d," , arr[i]);
        left = i;
        right += n/pow(2 , level);
        if(right >= n && left < n)
            right = n - 1;
        count++;
    }
}

void merge(int arr[] , int left , int middle, int right , int prNumber){

}