
#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

void
sllist_init(SLList * list)
{
	list->head = NULL;
}
int sllist_exists(SLList * list, int value) {
	SLEntry * e;
	e = list->head;
	while (e != NULL) {
		if(value == e->value) return 1;
		e = e->next; }
	return 0;
}
void sllist_add(SLList * list, int value) {
	// Create new node
	SLEntry * n = (SLEntry *) malloc(sizeof(SLEntry));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

// Add int value to the end of list. The values may be repeated.
void
sllist_add_end( SLList *list, int value )  {
	SLEntry *c,*p = NULL;
	if (list->head == NULL) {sllist_add(list,value);return;}
	for (c = list->head; c != NULL;p=c,c = c->next);// printf("Inside for insert_last%d\n");
	SLEntry * n = (SLEntry *) malloc(sizeof(SLEntry));
	p->next = n;
	n->value = value;
	n->next = NULL;
}


// Remove first occurrence of value in the list. It returns 1 if value is found or 0 otherwise.
int sllist_remove(SLList *list, int value) {
 SLEntry *c, *p; p = NULL;
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


// Removes from the list and frees the nodes of all the items that are min <= value <= max
void sllist_remove_interval(SLList *list, int min, int max) {
	SLEntry *c, *p; p = NULL;
	SLEntry *n = list->head;
	int i = 0; int flag = 0;
	for (c = list->head; c != NULL; p = c, c = c->next,flag = 0) {
		n = c;
		while(c->value >= min && c->value <= max) {
			//printf("Times:%i, Value: %i\n",i++,c->value);
    		if (p == NULL) list->head = c->next;
    		if(c->next == NULL) {c = NULL; break;}
			c = c->next; flag = 1;
		}
		if(p!=NULL && flag == 1) p->next = c;
		c = n;
   }
}


// It allocates and returns a new list with the intersection of the two lists, that is the 
// list of all the items that are common to the two lists. The items in the intersection are
// unique. 
SLList *
sllist_intersection(SLList *a, SLList *b) {
	SLList *c = (SLList *)malloc(sizeof(SLList)); 
	//printf("Hii\n");
	sllist_init(c);
	//SLList *c = &ab;		
	//printf("Hii\n");
	SLEntry *e, *p;
	int i = 0; int flag = 0;
	for (e = a->head; e != NULL; e = e->next) {
		for(p = b->head; p != NULL; p = p->next) {
			if(p->value == e->value) {
				if(c->head == NULL) { sllist_add(c,p->value); }
				else if (sllist_exists(c,e->value) == 0) { sllist_add(c,e->value); }
				//printf("yolo %i\n", e->value);
			}
			//printf("Buddhi Illayi %i\n",x);
		}
	}	
	return c;
}

void sllist_print(SLList *list)
{
	// Move to the end
	SLEntry * e = list->head;

	printf("--- List ---\n");
	while (e!= NULL) {
		printf("val=%d\n", e->value);
		e = e->next;
	}
}

