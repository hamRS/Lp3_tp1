#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define DELIMETER ","


int * nums_global;

/*prototypes*/
int * get_int_argv(char c_nums[] , char * delimeter);
int start_process(int prN , int * numbers);
void print_header(int prN , int n);
void print_arrLevel(int level, int counter , int prN , int n);
void print_treeMap( int prN , int n);
int merge_sort_process(int left , int right , int prN , int maxProcess);
void merge_process(int left , int middle , int right , int prN);

void print_array(int left , int right);
/*end of prototypes*/

int main(int argc , char * argv[]){
    if(argc != 3){
        fprintf(stderr , "Usage: %s <processes> <numbers>\n", argv[0]);
        return -1;
    }
    int nbr_processes = atoi(argv[1]);
    int * numbers = get_int_argv(argv[2] , DELIMETER);
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



int start_process(int prN , int * numbers){
    int i,j;
    nums_global = (int *) malloc(sizeof(int)*numbers[i]); 
    for(i = 0 ; i < numbers[0] ; i++)
        nums_global[i] = numbers[i + 1];
    int left,right;

    printf("===Esquema de arbol===\n");
    //print nums mapping 
    print_treeMap(prN, numbers[0]);
    printf("===mapeos===\n");
    merge_sort_process(0 , numbers[0] - 1 , 0 , prN );
    return 0;
}


int merge_sort_process( int left , int right , int prN , int maxProcess){

    return 0;
}

void merge_process(int left , int middle , int right , int prN){
    printf("===procesamiento===\n");
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
