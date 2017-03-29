#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
struct node
{
    int value;
    struct node * next;
};
typedef struct node node;

node * list_init()
{
    return NULL;
}

int empty_list(node * list)
{
    return list == NULL;
}

node * push_back(node * list,int value)
{
    node * n;
    n = (node *) malloc(sizeof(node));
    n->value = value;
    n->next = 0;
    if(empty_list(list))
        return n;
    node * head = list;
    while(list->next != 0)
        list = list->next;
    list->next = n;
    return head;
}
node * pop_back(node * list)
{
    if(empty_list(list))
        return 0;
    if(list->next == 0)
    {
        free(list) ;
        return 0;
    }

    node * head = list;
    while(list->next->next != 0)
        list = list->next;
    free(list->next);
    list->next = 0;
    return head;

}
node * push_front(node * list , int value)
{
    node * n;
    n = (node *) malloc(sizeof(node));
    n->value = value;
    n->next = list;
    list = n;
    return list;
}
node * pop_front(node * list)
{
    if(empty_list(list))
        return 0;
    node * next = list->next;
    free(list);
    return next;
}

void print_list(node * list)
{
    if(empty_list(list))
        return;
    while(list != 0)
    {
        printf("%d ",list->value);
        list = list->next;
    }
}



int main()
{
    freopen("input.in.c","r",stdin);
    node * list;
    list = list_init();
    int i ;
    for(i = 0 ;i<10;i++)
    {
        int v;
        scanf("%d",&v);
        list = push_back(list,v);
    }
    list = pop_front(list);
    list = push_front(list,-1);


    print_list(list);
    return 0;
}
