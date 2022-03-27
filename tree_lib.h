/*struct definitions*/
struct node {
    struct node * left;
    struct node * right;
    int b_full;
    int key;
}
/*end structures*/

/*prototypes*/
struct node * new_node(int data);
void levelOrder(struct node * root , int arr[], int * index , int n, int h);
void printCurrentLevel(struct node * root, int level, int arr[], int * index);
void createTree(struct node** node, int  max_proces, int * count_proc, int h, int h_max);
/*end prototypes*/



/*functions that spawns the tree array*/
struct node * new_node(int data){
    struct node * tmp = (struct node * ) malloc(sizeof(struct node));
    tmp->key = data;
    tmp->b_full = 0;
    tmp->left = tmp->right = NULL;
    return tmp;
}

void levelOrder(struct node * root , int arr[], int * index , int n, int h){
    int i;
    for(i = 1 ; i<= h ; i++)
        printCurrentLevel(root , i , arr, index);
}

void printCurrentLevel(struct node * root, int level, int arr[], int * index){
    if(root == NULL)
        return;
    if(level == 1){
        arr[((*index)++)] = root->key;
    }else if(level > 1){
        printCurrentLevel(root->left, level - 1 , arr, index);
        printCurrentLevel(root->right, level - 1 , arr, index);
    }   
}

void createTree(struct node** node, int  max_proces, int * count_proc, int h, int h_max){
    if(*count_proc < max_proces && h < h_max ){
        struct node * tmp = new_node(*count_proc);
        *node = tmp;
        (*count_proc)++;
        createTree(&(tmp->left) , max_proces , count_proc , h + 1 , h_max );
        if(*count_proc < max_proces){
            createTree(&(tmp->right) , max_proces , count_proc , h + 1 , h_max );
        }
    }
}

/*end functions that spawns the tree array*/