#include<stdio.h>
#include<stdlib.h>



/*prototypes*/
void merge_sort(int arr[] , int left , int right);
void merge(int arr[], int left , int middle , int right);
void print_array(int arr[], int n);
/*end prototypes*/
int main(){
    int n;
    scanf("%d" , &n);
    int arr[n];
    int i;
    for(i = 0 ; i < n ; i++)
        scanf("%d" , arr + i);
    merge_sort(arr , 0 , n - 1);
    print_array(arr , n);
}

void print_array(int arr[], int n){
    int i;
    for(i = 0; i < n ; i++ )
        printf("%d, " , arr[i]);
    printf("\n");
}

void merge_sort(int arr[], int left , int right){
    if(left < right){
        int p = left + (right - left)/2;
        merge_sort(arr , left , p);
        merge_sort(arr , p + 1 , right); 
        merge(arr , left , p , right);
    }
}


void merge(int arr[] , int left , int middle , int right){
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