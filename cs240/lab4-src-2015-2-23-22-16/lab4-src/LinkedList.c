
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	ListNode * e;
	e = list->head;
	while (e != NULL) {
		if(value == e->value) return 1;
		e = e->next; }
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode *c, *p; p = NULL;
	for (c =  list->head; c != NULL; p = c, c = c->next) {
	  if (c->value == value) {
	    if (p == NULL) list->head = c->next;
	    else p->next = c->next;
	    free(c);
	    return 1;
	  }
	}
	return 0;
}
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode *c; int i;
	for (c =  list->head,i=0; c != NULL; c = c->next,i++) if(i == ith){ *value = c->value;return 1; }
	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode *c, *p; p = NULL; int i;
	for (c =  list->head,i=0; c != NULL;p = c, c = c->next,i++) 
	{ if(i == ith){
	    if (p == NULL) list->head = c->next;  
	    else p->next = c->next;
	    free(c);
	    return 1; 
	  }
	}
	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	ListNode *c; int i;
	for (c =  list->head, i=0; c != NULL; c = c->next,i++);
	return i;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	//printf("Before opening the file\n");
	FILE * fd = fopen(file_name, "w");
	if (fd == NULL) return 0;
	ListNode *c;
	//printf("After opening the file\n");
	for (c = list->head; c != NULL; c = c->next) fprintf(fd, "%d\n",c->value);
	fclose(fd);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	FILE * fd = fopen(file_name, "w");
	if (fd == NULL) return 0;
	char *s;
	llist_init(list);
	while (0) {
	  fgets(s,sizeof(s),fd);
	  if (*s == EOF) break;
	  llist_add(list,atoi(s));
	}
	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
	int swapped, i;
	ListNode *p1,*p2 = NULL;
	if(p1 == NULL) return;
	if (ascending == 1) {
	  do {
	    swapped = 0;
	    p1 = list->head;
	    while (p1->next != p2) {
	      if (p1->value > p1->next->value) {
	        int temp = p1->value;
	        p1->value = p1->next->value;
	        p1->next->value = temp;
	        swapped = 1;
	      }
	      p1 = p1->next;
	    }
	    p2 = p1;
	  }while(swapped);
	}
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	if (list->head == NULL) return 0;
	ListNode *c=list->head;
	*value = c->value;
	list->head = c->next;
	free(c);
	return 1;
}


//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
	if(list->head == NULL) return 0;
	ListNode *c,*p;
	for (c =  list->head; c->next != NULL; p = c, c = c->next);	
	//printf("%d\n",c->value);
	*value = c->value;
	//printf("YOLO%d\n",*value);
	p->next = NULL;
	c = NULL;
	free(c);
	return 1;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
	llist_add(list,value);
	//printf("After insert_first \n");
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
	ListNode *c,*p = NULL;
	if (list->head == NULL) return;
	for (c = list->head; c != NULL;p=c,c = c->next);// printf("Inside for insert_last%d\n");
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	p->next = n;
	n->value = value;
	n->next = NULL;
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{ list->head = NULL;}
