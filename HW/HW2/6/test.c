#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int id;
    struct node *next;
}Node;

Node *gen_Node(int id){
    Node *new = malloc(sizeof(Node));
    new -> id = id;
    new -> next = NULL;
    return new;
}

typedef struct list{
    Node *head;
    Node *tail;
}List;

List *gen_list(){
    List *new = malloc(sizeof(List));
    new -> head = NULL;
    new -> tail = NULL;
    return new;
}

List *gen_adj_list(int n){
    List **new = malloc(sizeof(List*)*n);
    for(int i = 0; i < n; i++){
        new[i] = gen_list();
    }
    return new;
}

void node_enter(Node *a, List *b){
    if(b -> head == NULL && b -> tail == NULL){
        b -> head = a;
        b -> tail = a;
        return;
    }
    b -> tail -> next = a;
    b -> tail = a;
    return;
}

void traverse(int road[], List **list, int start){
    Node *node = list[start] -> head;
    while(node != NULL){
        if(road[node -> id] == -1){
            road[node -> id] = start;
            DFS(road, list, node -> id);
            node = node -> next;
        }
        else
            node = node -> next;
    }
    return;
}

int main(void){
    int n, q, s, r;
    s -= 1;
    r -= 1;
    scanf("%d%d%d%d", &n, &q, &s, &r);
    List **list = gen_adj_list(n);
    
    for(int i = 0; i < n; i++){

    }
}