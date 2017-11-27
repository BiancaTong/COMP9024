// Queue ADT header file ... COMP9024 17s2
// Written by Bianca Tong for COMP9024 ass2
#define MAX_WORD_LENGTH 20

typedef struct node {
   char data[MAX_WORD_LENGTH];
   struct node *next;
} NodeT;

typedef struct QueueRep {
   int   length;
   NodeT *head;
   NodeT *tail;
} QueueRep;

typedef struct QueueRep *queue;

queue newQueue();               // set up empty queue
void  dropQueue(queue);         // remove unwanted queue
int   QueueIsEmpty(queue);      // check whether queue is empty
void  QueueEnqueue(queue, char*); // insert an char at end of queue
void  QueueEnqueue_front(queue , char *);  // insert an char in front of queue
char* QueueDequeue(queue);      // remove char from front of queue
