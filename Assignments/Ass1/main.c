/**
     main.c

     Program supplied as a starting point for
     Assignment 1: Student record manager
     Written by Bianca Tong
     COMP9024 17s2
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "studentRecord.h"
#include "studentLL.h"

void printHelp();
void StudentLinkedListProcessing();

int main(int argc, char *argv[])
{
   if (argc == 2)
   {
	   //to build a dynamic array to store n student records from user input
	   int n=atoi(argv[1]);
	   studentRecordT*records = malloc(n*sizeof(studentRecordT));
	   for(int i=0;i<n;i++)
	   {
		   int stu_id=readValidID();
		   records[i].zID=stu_id;
	       int cre_pt=readValidCredits();
		   records[i].credits=cre_pt;
	       float wam=readValidWAM();
		   records[i].WAM=wam;
	   }
	   //to caculate Average WAM and Weighted average WAM
	   float a_wam;
	   float aa_wam=0.000;
	   float w_wam=0.000;
	   float ww_wam=0.000;
	   int nn=0;
	   for(int i=0;i<n;i++)
	   {
		   printStudentData(records[i].zID,records[i].credits,records[i].WAM);
		   aa_wam+=(float)records[i].WAM;
		   ww_wam+=(float)(records[i].credits*records[i].WAM);
		   nn+=records[i].credits;
	   }
	   a_wam=(float)aa_wam/n;
	   w_wam=(float)ww_wam/nn;
	   printf("Average WAM: %.3f\n",a_wam);
	   printf("Weighted average WAM: %.3f\n",w_wam);
   }
   else
   {
      StudentLinkedListProcessing();
   }
   return 0;
}

/* Code for Stages 2 and 3 starts here */

void StudentLinkedListProcessing()
{
   int op, ch;
   List list = newLL();   // create a new linked list

   while (1)
   {
      printf("Enter command (a,f,g,p,q, h for Help)> ");

      do
      {
    	  ch = getchar();
      }
      while (!isalpha(ch) && ch != '\n');  // isalpha() defined in ctype.h
      op = ch;
      // skip the rest of the line until newline is encountered
      while (ch != '\n')
      {
    	  ch = getchar();
      }
      switch (op)
      {
         case 'a':
         case 'A':
         {
        	 int zid=readValidID();
        	 int ct=readValidCredits();
        	 float wwam=readValidWAM();
        	 insertLL(list,zid,ct,wwam);
        	 break;
         }

         case 'f':
         case 'F':
         {
        	 int z_id=readValidID();
        	 inLL(list,z_id);
        	 break;
         }

         case 'g':
         case 'G':
         {
        	 int *N=malloc(sizeof(int));
        	 float *wamm=malloc(sizeof(float));
        	 float *W_wam=malloc(sizeof(float));
        	 getStatLL(list,N,wamm,W_wam);
        	 free(N);
        	 free(wamm);
        	 free(W_wam);
        	 break;
         }

         case 'h':
         case 'H':
             printHelp();
             break;

         case 'p':
         case 'P':
        	 showLL(list);
        	 break;

	     case 'q':
         case 'Q':
         {
             dropLL(list);
	         printf("Bye.\n");
	         return;
         }
      }
   }
}

void printHelp()
{
   printf("\n");
   printf(" A - Add student record\n" );
   printf(" F - Find student record\n" );
   printf(" G - Get statistics\n" );
   printf(" H - Help\n");
   printf(" P - Print all records\n" );
   printf(" Q - Quit\n");
   printf("\n");
}
