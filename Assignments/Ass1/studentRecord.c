// Student record implementation ... Assignment 1 COMP9024 17s2
// Written by Bianca Tong for comp9024 ass1
#include <stdio.h>

#define LINE_LENGTH 1024

// scan input for a positive integer, returns -1 if none
int readInt(void) {
   char line[LINE_LENGTH];
   int  n;

   fgets(line, LINE_LENGTH, stdin);
   if ( (sscanf(line, "%d", &n) != 1) || n <= 0 )
      return -1;
   else
      return n;
}

// scan input for a positive floating point number, returns -1 if none
float readFloat(void) {
   char  line[LINE_LENGTH];
   float f;

   fgets(line, LINE_LENGTH, stdin);
   if ( (sscanf(line, "%f", &f) != 1) || f <= 0.0 )
      return -1;
   else
      return f;
}

/*** Your code for stage 1 starts here ***/
//To justify the student ID : should be a 7-digit number
int readValidID(void)
{
	int stu_id=-1;
	int x=0;
	while(stu_id==-1)
	{
		if(x==0)
		{
		    printf("Enter student ID: ");
		}
	    stu_id=readInt();
	    if(stu_id==-1)
	    {
		    printf("Not valid. Enter a valid value: ");
		    x++;
		    continue;
	    }
	    if(stu_id>=10000000||stu_id<=999999)
		{
		    printf("Not valid. Enter a valid value: ");
		    stu_id=-1;
		    x++;
		    continue;
		}
	}
	return stu_id;
}
//To justify the credit points : should be a number between 2 and 480
int readValidCredits(void)
{
    int cre_pt=-1;
    int y=0;
    while(cre_pt==-1)
	{
		if(y==0)
		{
			printf("Enter credit points: ");
		}
		cre_pt=readInt();
	    if(cre_pt==-1)
	    {
		    printf("Not valid. Enter a valid value: ");
		    y++;
		    continue;
	    }
	    if((cre_pt>480)||(cre_pt<2))
	    {
	    	printf("Not valid. Enter a valid value: ");
	    	cre_pt=-1;
	    	y++;
	    	continue;
	    }
	    else
	    {
	    	break;
	    }
	}
    return cre_pt;
}
//To justify the wam : should be a floating point number between 50 and 100
float readValidWAM(void)
{
    float wam=-1;
	int z=0;
	while(wam==-1)
	{
		if(z==0)
		{
			printf("Enter WAM: ");
		}
		wam=readFloat();
	    if(wam==-1)
	    {
		    printf("Not valid. Enter a valid value: ");
		    z++;
		    continue;
	    }
		if ((wam>100)||(wam<50))
		{
		    printf("Not valid. Enter a valid value: ");
		    z++;
		    wam=-1;
		    continue;
		}
	}
	return wam;
}
//To show the output
void printStudentData(int zID, int credits, float WAM)
{
	printf("------------------------\n");
	printf("Student zID: z%d\n",zID);
	printf("Credits: %d\n",credits);
	char *pf;
	if((WAM>=85)&&(WAM<=100))
	{
		pf="HD";
	}
	else if((WAM>=75)&&(WAM<85))
	{
		pf="DN";
	}
	else if((WAM>=65)&&(WAM<75))
	{
		pf="CR";
	}
	else//((WAM>=50)&&(WAM<=64))
	{
		pf="PS";
	}
	printf("Level of performance: %s\n",pf);
	printf("------------------------\n");
	return;
}
