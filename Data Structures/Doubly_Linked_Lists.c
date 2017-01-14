#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node * next;
	struct node * previous;
}node_t ;

typedef struct list
{
	struct node * begin;
	struct node * end;
}list_t;

int empty_list(list_t * l)
{
	return (l->begin->next == l->end);
}

list_t * new_list()
{
	list_t * l = (list_t *) malloc(sizeof(list_t));
	node_t * begin = (node_t *) malloc(sizeof(node_t));
	node_t * end = (node_t *) malloc(sizeof(node_t));
	begin->next = end;
	end->previous = begin;
	begin->previous = end->next = 0;
	l->begin = begin;
	l->end = end;
	return l;
}

void push_back(list_t * l,int value)
{
	node_t * end = l->end;
	node_t * node = (node_t *) malloc(sizeof(node_t));
	node->value = value;
	node->next = end;
	node->previous = end->previous;
	end->previous->next = node;
	end->previous = node;
	
}

void pop_back(list_t * l)
{
	if(empty_list(l))
		return ;
	node_t * end = l->end;
	end->previous = end->previous->previous;
	free(end->previous->next);
	end->previous->next = end;
}

void push_front(list_t * l,int value)
{
	node_t * begin = l->begin;
	node_t * node = (node_t *) malloc(sizeof(node_t));
	node->value = value;
	node->next = begin->next;
	node->previous = begin;
	begin->next->previous = node;
	begin->next = node;
	
}
void pop_front(list_t * l)
{
	if(empty_list(l))
		return ;
	node_t * begin = l->begin;
	begin->next = begin->next->next;
	free(begin->next->previous);
	begin->next->previous = begin;
}


void print_list(list_t * l)
{
	node_t * iterator = l->begin->next;
	while(iterator != l->end)
	{
		printf("%d\t",iterator->value);
		iterator = iterator->next;
	}
	printf("\n");
}
void clear_list(list_t * l)
{
	node_t * begin = l->begin;
	node_t * end = l->end;
	node_t * iterator = l->begin->next;
	while(iterator != l->end)
	{
		free(iterator);
		iterator = iterator->next;
	}
	begin->next = end;
	end->previous = begin;
}



int main()
{
	list_t * l1 = new_list();
	int i;
	for (i=0;i<10;i++)
		push_back(l1,i);
	for (i=0;i<5;i++)
		pop_front(l1);
		
	print_list(l1);
	return 0;
}
