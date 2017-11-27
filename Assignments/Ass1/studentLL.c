## Written by Bianca Tong for COMP9024 ass1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "studentLL.h"
#include "studentRecord.h"

// linked list node type
// DO NOT CHANGE
typedef struct node
{
    studentRecordT data;
    struct node    *next;
} NodeT;

// linked list type
typedef struct ListRep
{
   NodeT *head;

/* Add more fields if you wish */

} ListRep;

/*** Your code for stages 2 & 3 starts here ***/

// Time complexity:O(1)
// Explanation:Just build a new null list.
// To initialize a new List using type List
List newLL()
{
	ListRep *LL=malloc(sizeof(ListRep));
	assert(LL!=NULL);
	LL->head=NULL;
	return LL;
	/*
	NodeT *p1;
	p1=(NodeT *)malloc(sizeof(NodeT));
	assert(p1 != NULL);
	p1->data.zID=0;
	p1->data.credits=0;
	p1->data.WAM=0.000;
	p1->next=NULL;
	LL->head=p1;
	free(p1);
	*/
}

// Time complexity:O(n)
// Explanation:There is a loop to drop all of the elements(n times).
// When typing q or Q : should drop all the list
void dropLL(List listp)
{
	//NodeT *p2=malloc(sizeof(NodeT));
	//assert(p2!=NULL);
	NodeT *p2=listp->head;
	while (p2!=NULL)
	{
		//NodeT *p3=malloc(sizeof(NodeT));
		//assert(p3!=NULL);
		NodeT *p3;
		p3=p2->next;
	    free(p2);
	    p2=p3;
	}
	free(listp);
	//free(p3);
	return;
}

// Time complexity:O(n)
// Explanation: need to loop in the list to find the special node.
// When typing f or F : should find out the student record according to his/her ZID
// If not exists, should print "No record found."
void inLL(List listp, int zid)
{
	//NodeT *p4 = malloc(sizeof(NodeT));
	//assert(p4!=NULL);
	NodeT *p4;
	for (p4=listp->head;p4!=NULL;p4=p4->next)
	{
		if (p4->data.zID==zid)
		{
			printStudentData(zid,p4->data.credits,p4->data.WAM);
			//free(p4);
			return;
		}
	}
	//free(p4);
	printf("No record found.\n");
	return;
}

// Time complexity:O(1) for stage 2 and O(n) for stage 3
// Explanation:Stage 2 only need to insert in the beginning of the list, so the compleity is  O(1)
// Explanation:Stage 3 may need to loop all of the list elements to find the correct space to insert.
// stage 2:: When typing a or A : should insert new record into the beginning of the linked list
// stage 2:: Output  "Student record added."
// stage 3:: New records should now be inserted into the list in ascending order of the student ID
// stage 3:: Existing records should be updated with new data
// stage 3:: Output   "Student record updated."
void insertLL(List listp, int zid, int cr, float wam)
{
	//stage 2
	/*
	NodeT *new=malloc(sizeof(NodeT));
	assert(new!=NULL);
	new->data.zID=zid;
	new->data.credits=cr;
	new->data.WAM=wam;
	new->next=listp->head;
	listp->head=new;
	printf("Student record added.\n");
	//printStudentData(new->data.zID,new->data.credits,new->data.WAM);
	//printStudentData(listp->head->data.zID,listp->head->data.credits,listp->head->data.WAM);
	//free(new);
	return;
	*/
	//stage 3
	NodeT *new=malloc(sizeof(NodeT));
	assert(new!=NULL);
	new->data.zID=zid;
	new->data.credits=cr;
	new->data.WAM=wam;
	//if listp is empty or the new zid is smaller than the head, just insert in the beginning
	if(listp->head==NULL||zid<listp->head->data.zID)
	{
		new->next=listp->head;
		listp->head=new;
		printf("Student record added.\n");
		return;
	}
	//else if the new zid is equal with the head, just update the head
	else if(zid==listp->head->data.zID)
	{
	    new->next=listp->head->next;
	    free(listp->head);
	    listp->head=new;
	    printf("Student record updated.\n");
	    return;
	}
	//else if the new zid is larger than the head, should find next node until find a node
	//if the node is larger than the new zid, then insert the new zid in front of this node
	//else the node is equal with the new zid, then update this node
	else
	{
		NodeT *p7=listp->head;
		while(p7->next!=NULL)
		{
			if(zid<p7->next->data.zID)
			{
				new->next=p7->next;
				p7->next=new;
				printf("Student record added.\n");
				return;
			}
			else if(zid==p7->next->data.zID)
			{
				new->next=p7->next->next;
				free(p7->next);
				p7->next=new;
				printf("Student record updated.\n");
				return;
			}
			else
			{
				p7=p7->next;
			}
		}
		//eventually, if no larger node found, then insert the new node at the end of the list
		new->next=NULL;
		p7->next=new;
		printf("Student record added.\n");
		return;
	}
}

// Time complexity:O(n)
// Explanation:need to loop in the whole list to compute those statistics.
// When typing g or G : should compute the total number of records, average WAM and weighted average WAM
void getStatLL(List listp, int *n, float *wam, float *w_wam)
{
	 int nn=0;
	 int nnn=0;
	 float aaa_wam=0;
	 float www_wam=0;
	 NodeT *p5=malloc(sizeof(NodeT));
	 assert(p5!=NULL);
	 p5=listp->head;
	 while (p5!=NULL)
	 {
		 nnn++;
		 aaa_wam+=(float)(p5->data.WAM);
		 www_wam+=(float)(p5->data.credits*p5->data.WAM);
		 nn+=p5->data.credits;
		 p5=p5->next;
	 }
	 n=&nnn;
	 float xx=(float)(aaa_wam/nnn);
	 wam=&xx;
	 float yy=(float)(www_wam/nn);
	 w_wam=&yy;
	printf("Number of records: %d\n",*n);
	printf("Average WAM: %.3f\n",*wam);
	printf("Average weighted WAM: %.3f\n",*w_wam);
	free(p5);
	return;
}

// Time complexity:O(n)
// Explanation:of course is O(n), cause we need to show all of the records in the list.
// When typing p or P : should print all student records
void showLL(List listp)
{
	NodeT *p6=malloc(sizeof(NodeT));
	assert(p6!=NULL);
	//while (p6!=NULL);
	for (p6=listp->head;p6!=NULL;p6=p6->next)
	{
		printStudentData(p6->data.zID,p6->data.credits,p6->data.WAM);
	}
	free(p6);
	return;
}

