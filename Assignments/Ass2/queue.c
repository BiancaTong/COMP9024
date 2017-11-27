// Queue ADT implementation ... COMP9024 17s2
// Written by Bianca Tong for COMP9024 ass2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

#define MAX_WORD_LENGTH 20

// set up empty queue
queue newQueue() {
   queue Q = malloc(sizeof(QueueRep));
   Q->length = 0;
   Q->head = NULL;
   Q->tail = NULL;
   return Q;
}

// remove unwanted queue
void dropQueue(queue Q) {
   NodeT *curr = Q->head;
   while (curr != NULL) {
      NodeT *temp = curr->next;
      free(curr);
      curr = temp;
   }
   free(Q);
}

// check whether queue is empty
int QueueIsEmpty(queue Q) {
   return (Q->length == 0);
}

// insert an char at end of queue
void QueueEnqueue(queue Q, char *v) {
   NodeT *new = malloc(sizeof(NodeT));
   assert(new != NULL);
   strcpy(new->data, v);
   new->next = NULL;
   if (Q->tail != NULL) {
      Q->tail->next = new;
      Q->tail = new;
   } else {
      Q->head = new;
      Q->tail = new;
   }
   Q->length++;
}

// insert an char in front of queue
void QueueEnqueue_front(queue Q, char *v) {
   NodeT *new = malloc(sizeof(NodeT));
   assert(new != NULL);
   strcpy(new->data, v);
   if (Q->length!=0) {
   	  new->next=Q->head;
   	  Q->head=new;
      } else {
         Q->head = new;
         Q->tail = new;
      }
   Q->length++;
}

// remove char from front of queue
char* QueueDequeue(queue Q) {
   assert(Q->length > 0);
   NodeT *p = Q->head;
   Q->head = Q->head->next;
   if (Q->length==1) {
         Q->tail = NULL;
      }
   Q->length--;
   char *d=(char *) malloc (MAX_WORD_LENGTH*sizeof(char*));
   strcpy(d, p->data);
   free(p);
   return d;
}
