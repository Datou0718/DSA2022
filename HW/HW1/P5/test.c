#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Usb{
    int id;
    struct Usb *pointer[2];//two direction
}USB;
typedef struct group{
    int id;
    USB *group_head, *group_tail;//head and tail of the group
    struct group *prev, *next;//previous group and next group
}Group;
typedef struct toilet{
    int close;//1 for closed, 0 for open
    Group *toilet_head, *toilet_tail;//head and tail of the toilet
    Group **groups;
}Toilet;
USB *genUSB(int id){
    USB *new = malloc(sizeof(USB));
    new -> id = id;
    new -> pointer[0] = NULL;
    new -> pointer[1] = NULL;
    return new; 
}
int flip(int n){
    n = (n == 1)? 0 : 1;
    return n;
}
void USB_enter(USB *new, Group *group){
    if(group -> group_head == NULL && group -> group_tail == NULL){
        group -> group_head = new;
        group -> group_tail = new;
        return;
    }
    int dir = (group -> group_tail -> pointer[1] == NULL)? 1 : 0;
    group -> group_tail -> pointer[dir] = new;
    new -> pointer[flip(dir)] = group -> group_tail;
    group -> group_tail = new;
    return;
}
void USB_leave(Group *group){
    if(group -> group_head == group -> group_tail){
        group -> group_head = NULL;
        group -> group_tail = NULL;
        return;
    }
    USB *new = group -> group_tail;
    int dir = (new -> pointer[1] == NULL)? 0 : 1;
    USB *tmp = new -> pointer[dir];
    dir = (tmp -> pointer[1] == new)? 1 : 0;
    tmp -> pointer[dir] = NULL;
    group -> group_tail = tmp;
    return;
}
void USB_go(Group *group){
    if(group -> group_head == group -> group_tail){
        group -> group_head = NULL;
        group -> group_tail = NULL;
        return;
    }
    USB *new = group -> group_head;
    int dir = (group -> group_head -> pointer[0] == NULL)? 1 : 0;
    USB *tmp = new -> pointer[dir];
    dir = (tmp -> pointer[0] == new)? 0 : 1;
    tmp -> pointer[dir] = NULL;
    group -> group_head = tmp;
    return;
}
Group *genGroup(int id){
    Group *new = malloc(sizeof(Group));
    new -> id = id;
    new -> group_head = NULL;
    new -> group_tail = NULL;
    new -> prev = NULL;
    new -> next = NULL;
    return new;
}
void group_enter(Toilet *t, Group *group){
    if(t -> toilet_head == NULL && t -> toilet_tail == NULL){
        t -> toilet_head = group;
        t -> toilet_tail = group;
        return;
    }
    t -> toilet_tail -> next = group;
    group -> prev = t -> toilet_tail;
    t -> toilet_tail = group;
    return;
}
void group_leave(Toilet *t){
    if(t -> toilet_head == t -> toilet_tail){
        t -> toilet_head = NULL;
        t -> toilet_tail = NULL;
        return;
    }
    Group *new = t -> toilet_tail;
    new -> prev -> next = NULL;
    t -> toilet_tail = new -> prev;
    new -> group_head = NULL;
    new -> group_tail = NULL;
    new -> prev = NULL;
    new -> next = NULL;
    return;
}
void group_go(Toilet *t){
    if(t -> toilet_head == t -> toilet_tail){
        t -> toilet_head = NULL;
        t -> toilet_tail = NULL;
        return;
    }
    Group *new = t -> toilet_head;    
    new -> next -> prev = NULL;
    t -> toilet_head = new -> next;
    new -> group_head = NULL;
    new -> group_tail = NULL;
    new -> prev = NULL;
    new -> next = NULL;
    return;
}
Toilet *genToilet(int group_num){
    Toilet *t = malloc(sizeof(Toilet));
    t -> groups = malloc(sizeof(Group*)*group_num);
    t -> close = 0;
    t -> toilet_head = NULL;
    t -> toilet_tail = NULL;
    for(int i = 0; i < group_num; i++){
        t -> groups[i] = genGroup(i);
    }
    return t;
}
void print(Toilet *t[], int m){
    for(int i = 0; i < m; i++){
        Group *g = t[i] -> toilet_head;
        if(g == NULL || t[i] -> close == 1){
            printf("\n");
        }
        while(g != NULL && t[i] -> close != 1){
            USB *prt = g -> group_head;
            USB *prted = NULL;
            while(prt != NULL){
                printf("%d", prt -> id);
                if(prt == g -> group_tail && g == t[i] ->toilet_tail){
                    printf("\n");
                    break;
                }
                else
                    printf(" ");
                if(prt -> pointer[0] != prted){
                    prted = prt;
                    prt = prt -> pointer[0];
                }
                else{
                    prted = prt;
                    prt = prt -> pointer[1];
                }
            }
            g = g -> next;
        }
    }
    return;
}
void close(Toilet *a, Toilet *b){
    Group *g = a -> toilet_tail;
    while(g != NULL){
        int index = g -> id;
        if(b -> groups[index] -> group_head == NULL && b -> groups[index] -> group_tail == NULL){
            group_enter(b, b -> groups[index]);
            b -> groups[index] -> group_head = g -> group_tail;
            b -> groups[index] -> group_tail = g -> group_head;
        }
        else{
            int dir = (b -> groups[index] -> group_tail -> pointer[1] == NULL)? 1 : 0;
            b -> groups[index] -> group_tail -> pointer[dir] = g -> group_tail;
            int Dir = (g -> group_tail -> pointer[1] == NULL)? 1 : 0;
            g -> group_tail -> pointer[Dir] = b -> groups[index] -> group_tail;
            b -> groups[index] -> group_tail = g -> group_head;
        }
        g = g -> prev;
    }
    return;
}
int main(void){
    int toilet_num, cmd_num, group_num;
    scanf("%d%d%d", &toilet_num, &cmd_num, &group_num);
    char cmd[10];
    int I = 0, J = 0, M = 0; //j for id, i for group, m for toilet;
    Toilet **t = malloc(sizeof(Toilet*)*toilet_num);
    for(int i = 0; i < toilet_num; i++){
        t[i] = genToilet(group_num);
    }
    for(int i = 0; i < cmd_num; i++){
        scanf("%s", cmd);
        if(strcmp(cmd, "enter") == 0){
            scanf("%d%d%d", &I, &J, &M); //j for id, i for group, m for toilet;
            USB *new = genUSB(J);
            if(t[M] -> groups[I] -> group_head == NULL){
                group_enter(t[M], t[M] -> groups[I]);
            }
            USB_enter(new, t[M] -> groups[I]);
        }
        else if(strcmp(cmd, "leave") == 0){
            scanf("%d", &M);
            USB_leave(t[M] -> toilet_tail);
            if(t[M] -> toilet_tail -> group_head == NULL){
                group_leave(t[M]);
            }
        }
        else if(strcmp(cmd, "go") == 0){
            scanf("%d", &M);
            USB_go(t[M] -> toilet_head);
            if(t[M] -> toilet_head -> group_head == NULL){
                group_go(t[M]);
            }
        }
        else if(strcmp(cmd, "close") == 0){
            scanf("%d", &M);
            t[M] -> close = 1;
            int tmp = (M - 1 + toilet_num) % toilet_num; //if tmp = M - 1, tmp may be -1
            while(t[tmp] -> close == 1 && tmp != M){
                if(tmp > 0){
                    tmp -= 1;
                }
                else if(tmp == 0){
                    tmp = toilet_num - 1;
                }
            }
            if(tmp == M){
                print(t, toilet_num);
                return 0;
            }
            close(t[M], t[tmp]);
        }
    }
    print(t, toilet_num);
    return 0;
}
