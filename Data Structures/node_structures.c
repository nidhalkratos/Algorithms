/*
This code was written by Nidhal Abidi. Check out www.github.com/nidhalkratos for more info
You can use this code however you want, but note that it is provided as is and I'm not responsible for any miss use :P
This is a simple implementation for fondamental data structures and their basic operations

Linked list : Pushing to the front and the back and poping from the front and the back
Stacks 		: Pushing and poping
Queues 		: Pusing and poping 

Note : Since stacks and queues are linked lists too, their implementations rely on the code writen for the linked list
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node * next;
} node_t;

typedef node_t * list;
typedef list stack;
typedef list queue;

//Functions to initialize the datastructures (Make them point to null)
void init_list(list * l)
{
	*l = 0;
}
void init_stack(stack * s)
{
	init_list(s);
}
void init_queue(queue * q)
{
	init_list(q);
}

void push_back(list * l,int value)
{
	if((*l) == 0)
	{
		(*l) = (node_t *) malloc(sizeof(node_t));
		(*l)->value = value;
		(*l)->next = 0;
		return ;
	}
	node_t * node_ptr = (*l);
	
	while(node_ptr->next != 0)
		node_ptr = node_ptr->next;
	node_ptr->next = (node_t *) malloc(sizeof(node_t));
	node_ptr->next->value = value;
	node_ptr->next->next = 0;
	
}

void pop_back(list * l)
{
	if((*l) == 0)
		return ;
	if((*l)->next == 0)
	{
		free((*l));
		(*l) = 0;
		return;
	}
	node_t * node_ptr = (*l);
	while(node_ptr->next->next != 0)
		node_ptr = node_ptr->next;
	free(node_ptr->next);
	node_ptr->next = 0;
	
}

void push_front(list * l, int value)
{
	if((*l) == 0)
	{
		(*l) = (node_t *) malloc(sizeof(node_t));
		(*l)->value = value;
		(*l)->next = 0;
		return ;
	}
	node_t * node_ptr = (node_t *) malloc(sizeof(node_t));
	node_ptr->value = value;
	node_ptr->next = (*l);
	(*l) = node_ptr;
}

void pop_front(list * l)
{
	if((*l) == 0)
		return;
	node_t * second_node_ptr = (*l)->next;
	free(*l);
	(*l) = second_node_ptr;
}

void print_list(list * l)
{
	node_t * node_ptr = (*l);
	while(node_ptr != 0)
	{
		printf("%d\t",node_ptr->value);
		node_ptr = node_ptr->next;
	}
	printf("\n");
}

void print_stack(stack * s)
{
	print_list(s);
}

void print_queue(queue * q)
{
	print_list(q);
}

void push_stack(stack * s,int value)
{
	push_front(s,value);
}
void pop_stack(stack * s)
{
	pop_front(s);
}

void push_queue(queue * q,int value)
{
	push_back(q,value);
}

void pop_queue(queue * q)
{
	pop_front(q);
}

void test_list(list * l)
{
	push_back(l,3);
	push_back(l,4);
	push_back(l,2);	
	push_back(l,6);
	push_front(l,1);
	push_front(l,5);
	pop_back(l);
	pop_front(l);
}

void test_queue(queue * q)
{
	push_queue(q,7);
	push_queue(q,8);
	push_queue(q,9);
	push_queue(q,10);
	push_queue(q,11);
	pop_queue(q);
}

void test_stack(stack * s)
{
	push_stack(s,1);
	push_stack(s,2);
	push_stack(s,3);
	pop_stack(s);
}

int main()
{
	list l;
	stack s;
	queue q;
	init_list(&l);
	init_stack(&s);
	init_queue(&q);
	
	test_list(&l);
	test_queue(&q);
	test_stack(&s);
	printf("Printing list:\n");
	print_list(&l);
	printf("Printing stack:\n");
	print_stack(&s);
	printf("Printing queue:\n");
	print_queue(&q);
	return 0;
}
