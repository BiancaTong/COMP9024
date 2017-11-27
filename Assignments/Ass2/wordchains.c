/* Written by Bianca Tong for COMP9024 assignment2 in 8/10/2017*/

/*The main idea: */
/*[1] store all of the word in a queue; */
/*[2] traversal the whole queue to build a directed weighted graph */
/*    using the words as vertices; */
/*    generate a function to examine the related words; */
/*    using these related words as edges; */
/*[3] traversal the whole graph to find out all of the paths */
/*    using indexes instead of words to make records simpler; */
/*    after iteration, the result path is uncompleted form; */
/*    then generate a function to make all of the paths completed ; */
/*[4] find out the longest path in all of the paths */
/*    transfer the index path into word path and output the result. */

/*For instance, if the words chain is bear, beer, dear, deer, hear, heat, rear, seat. */
/*in step[3] of my idea: */
/*the uncompleted paths are: 0+1+3, 0+2+3, 2+4+5+7, 4+6, 2+6, 0+4+5+7, 4+6, 0+6 and so on.*/
/*the completed paths are: 0+1+3, 0+2+3, 0+2+4+5+7, 0+2+4+6, 0+2+6, 0+4+5+7, 0+4+6, 0+6 and so on.*/
/*in step[4] of my idea: */
/*the longest path in index is: 0+2+4+5+7. */
/*the longest path in words is: bear->dear->hear->heat->seat. */

/*For task 1, need to store in a queue, check for related words, make a graph and output relations. */
/*stage 1 time complexity is O(n2*m2) */

/*For task 2, need to find the longest chain and output the chain. */
/*stage 2 time complexity is O(n2) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "queue.h"
#include "WGraph.h"

#define MAX_WORD_LENGTH 20
#define FORMAT_STRING "%19s"
#define MAX_WORD_NUM 1000

Graph makegraph();
int relatestr();
queue findchain(Graph, queue, int);
void findfind(Graph, queue, int, int, int);
queue wellpath(queue ,int );

int main(int argc, char *argv[])
{
	/* input a positive number n to be the number of words */
	int n=0;
	printf("Enter a number: ");
	scanf("%d",&n);

	/* input n words and store in a queue */
	queue chain_queue=newQueue();
	queue copy_queue=newQueue();
	queue copyy_queue=newQueue();
	queue q1=newQueue();
	for(int i=0;i<n;i++)
	{
		char word[MAX_WORD_LENGTH];
		printf("Enter word: ");
		scanf(FORMAT_STRING, word);
		QueueEnqueue(q1, word);
		QueueEnqueue(chain_queue, word);
		QueueEnqueue(copy_queue, word);
	}
	printf("\n");

	/* get a graph from above queue to connect all of the words */
	Graph g=makegraph(chain_queue,n);

	/* find longest word chain and output */
	queue q2=newQueue();
	q2=findchain(g, q1, n);
	int q2_l=q2->length;
	for(int d=0;d<q2_l;d++)
	{
		char *path=QueueDequeue(q2);
		int mm=(strlen(path)+1)/2;
		if(d==0)
		{
			printf("Maximum chain length: %d\n",mm);
			printf("Maximal chains: \n");
		}
		int pr=0;
		for(int i=0;i<strlen(path);i=i+2)
		{
			int i_int=atoi(&path[i]);

			int yy=copy_queue->length;
			for(int j=0;j<yy;j++)
			{
				char* ff=QueueDequeue(copy_queue);
				QueueEnqueue(copyy_queue,ff);
				if(j==i_int)
				{
					if(pr==mm-1)
					{
						printf("%s\n", ff);
					}
					else
					{
						printf("%s -> ", ff);
					    pr++;
					}
				}
				free(ff);
			}

			int zz=copyy_queue->length;
			for(int k=0;k<zz;k++)
			{
				char* gg=QueueDequeue(copyy_queue);
				QueueEnqueue(copy_queue,gg);
				free(gg);
			}
		}
		free(path);
	}

	freeGraph(g);
	dropQueue(chain_queue);
	dropQueue(q1);
	dropQueue(q2);
	return(0);
}

/* build a graph with the length of every vertex */
Graph makegraph(queue q, int n)
{
	Graph chain_graph=newGraph(n);
	for(int i=0;i<n;i++)
	{
		char *x=QueueDequeue(q);
		printf("%s: ",x);
		queue qq=newQueue();
		for(int j=i+1;j<n;j++)
		{
			char *y=QueueDequeue(q);
			QueueEnqueue(qq, y);
			if(relatestr(x,y))
			{
				Edge new;
				strcpy(new.v,x);
				strcpy(new.w,y);
				new.weight=strlen(y);
				insertEdge(chain_graph, new, i, j);
				printf("%s ",y);
			}
			free(y);
		}
		for(int k=i+1;k<n;k++)
			{
				char *z=QueueDequeue(qq);
				QueueEnqueue(q, z);
				free(z);
			}
		dropQueue(qq);
		free(x);
		printf("\n");
	}
	printf("\n");
	return(chain_graph);
}

/* To justify whether two word are related */
int relatestr(char *x, char *y)
{
	int n=0;
	int S=1;
	if(strlen(x)==strlen(y))
	{
		for(int i=0;i<strlen(x);i++)
			{
				if(x[i]!=y[i])
				{
					n++;
				}
				if(n>1)
				{
					S=0;
					break;
				}
			}
	}
	else if(strlen(x)==strlen(y)+1)
	{
		for(int i=0;i<strlen(x);i++)
		{
			char dest1[MAX_WORD_LENGTH]="";
			char dest2[MAX_WORD_LENGTH]="";
			if(i==0)
			{
				strncpy(dest2,x+i+1,strlen(x)-i-1);
				if(strcmp(dest1,y)==0)
				{
					break;
				}
				else
				{
					if(i==strlen(x)-1)
					{
						S=0;
					}
				}
			}
			else
			{
				strncpy(dest1,x,i);
				strncpy(dest2,x+i+1,strlen(x)-i-1);
				strcat(dest1,dest2);
				if(strcmp(dest1,y)==0)
				{
					break;
				}
				else
				{
					if(i==strlen(x)-1)
					{
						S=0;
					}
				}
			}
		}
	}
	else if(strlen(x)==strlen(y)-1)
	{
		for(int i=0;i<strlen(y);i++)
		{
			char dest1[MAX_WORD_LENGTH]="";
			char dest2[MAX_WORD_LENGTH]="";
			if(i==0)
			{
				strncpy(dest2,y+i+1,strlen(y)-i-1);
				if(strcmp(dest1,x)==0)
				{
					break;
				}
				else
				{
					if(i==strlen(y)-1)
					{
						S=0;
					}
				}
			}
			else
			{
				strncpy(dest1,y,i);
				strncpy(dest2,y+i+1,strlen(y)-i-1);
				strcat(dest1,dest2);
				if(strcmp(dest1,x)==0)
				{
					break;
				}
				else
				{
					if(i==strlen(y)-1)
					{
						S=0;
					}
				}
			}
		}
	}
	else
	{
		S=0;
	}
	if(S)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

/* find the maximum length of chains */
queue findchain(Graph g, queue q, int n)
{
	queue q1=newQueue();
	queue rx=newQueue();
	int lmax=1;
	queue numm=newQueue();
	queue cp=newQueue();
	char delim[2] = {'+'};
	int maxlength=1;

	for(int i=0;i<n;i++)
	{
		findfind(g,q1,i,n,lmax);
		int num=q1->length-1;
		char string[MAX_WORD_NUM*2]="";

		for(int j=0;j<num;j++)
		{
			char *x=QueueDequeue(q1);

			if(strlen(x)==3)
			{
				if(strlen(string)==0)
				{
					strcpy(string,x);
				}
				else
				{
					char xx[2]="";
					strncpy(xx,x+2,2);
					strcat(string,delim);
					strcat(string,xx);
				}

			}
			else
			{
				QueueEnqueue(numm,x);
				if(strlen(string)!=0)
				{
					QueueEnqueue(cp,string);
				}
				char c[2]="";
				strcpy(string,c);
			}
			if(j==num-1)
			{
				QueueEnqueue(cp,string);
				char c[2]="";
				strcpy(string,c);
			}
			free(x);
		}

		char *l=QueueDequeue(q1);
		free(l);


		if(cp->length==0)
		{
			continue;
		}
		queue r=newQueue();
		r=wellpath(cp,i);
		int r_num=r->length;
		queue nm=newQueue();
		queue rr=newQueue();

		int cma=0;
		for(int u=0;u<r_num;u++)
		{
			char *o=QueueDequeue(r);
			int Isdigit=1;
			for(int h=0;h<strlen(o);h++)
			{
				if(isdigit(o[h])==0)
				{
					Isdigit=0;
					break;
				}
			}
			if(Isdigit)
			{
				int int_o=atoi(o);

				if(int_o>cma)
				{
					cma=int_o;
					if(nm->length==0)
					{
						QueueEnqueue(nm,o);
					}
					else
					{
						char *ds=QueueDequeue(nm);
						QueueEnqueue(nm,o);
						free(ds);
					}
				}

			}
			else
			{
				QueueEnqueue(rr,o);
			}
		}
		dropQueue(r);
		int rr_num=rr->length;
		char *mmll=QueueDequeue(nm);
		int int_mmll=atoi(mmll);
		free(mmll);
		dropQueue(nm);
		int FLAG=0;
		if(maxlength<=int_mmll)
		{
			maxlength=int_mmll;
			for(int a=0;a<rr_num;a++)
			{
				char* b=QueueDequeue(rr);
				if(strlen(b)==int_mmll)
				{
					if(rx->length!=0)
					{
						if(!FLAG)
						{
							int rx_l=rx->length;
							for(int w=0;w<rx_l;w++)
							{
								char*tt=QueueDequeue(rx);
								free(tt);
							}
							QueueEnqueue(rx,b);
							free(b);
						}
						else
						{
							QueueEnqueue(rx,b);
							free(b);
						}
					}
					else
					{
						FLAG=1;
						QueueEnqueue(rx,b);
						free(b);
					}

				}
			}
		}
		dropQueue(rr);
	}
	dropQueue(cp);
	dropQueue(numm);
	return(rx);
	/*
	printf("Maximum chain length: %d\n",n);
	printf("Maximal chains: \n");
	for(int i=0;i<n;i++)
	{
		if(i==n-1)
		{
			char *x=QueueDequeue(q);
			printf("%s\n", x);
			free(x);
			break;
		}
		char *x=QueueDequeue(q);
		printf("%s -> ", x);
		free(x);
	}
	*/
}
 /* use iteration to find every linked chain */
void findfind(Graph g,queue q_max, int i, int n, int lmax)
{
	int length=lmax;
	queue q_sub=newQueue();
	for(int j=i+1;j<n;j++)
	{
		if(g->edges[i][j]!=0)
		{
			length++;
			char str[MAX_WORD_LENGTH*2+1];
			char strr[MAX_WORD_LENGTH];
			sprintf(str, "%d", i);
			char a[2]={'+'};
			strcat(str,a);
			sprintf(strr, "%d", j);
			strcat(str,strr);
			QueueEnqueue(q_sub,str);
			findfind(g, q_sub, j, n, length);
		}
	}
	int x=q_sub->length;
	if(x==0)
	{
		char l[MAX_WORD_LENGTH];
		sprintf(l, "%d", length);
		QueueEnqueue(q_max,l);
	}
	else
	{
		for(int m=0;m<x;m++)
		{
			char* ss=QueueDequeue(q_sub);
			QueueEnqueue(q_max,ss);
			free(ss);
		}
    }
}

/* to make every path completed */
queue wellpath(queue cp,int n)
{
	int len=cp->length;
	queue pre=newQueue();
	queue mid=newQueue();
	queue results=newQueue();
	for(int i=0;i<len;i++)
	{
		char* str=QueueDequeue(cp);
		char prestr[MAX_WORD_LENGTH]="";
		int f_num=atoi(&str[0]);
		int index=100;
		if(f_num==n)
		{
			QueueEnqueue_front(pre,str);
			QueueEnqueue(results,str);
			char l[MAX_WORD_LENGTH];
			sprintf(l, "%d", strlen(str));
			QueueEnqueue(results,l);
		}
		else
		{
			while(1)
			{
				char *cmp=QueueDequeue(pre);
			    for(int j=0;j<strlen(cmp);j++)
			    {
				    if(cmp[j]==str[0])
				    {
					    index=j;
					    break;
				    }
			    }
			    if(index!=100 && index!=0)
			    {
			    	strncpy(prestr,cmp,index);
			    	strcat(prestr,str);
			    	strcpy(str,prestr);
			    	int prestr_int=atoi(&prestr[0]);
			    	if(prestr_int!=n)
			    	{
			    		QueueEnqueue_front(mid,cmp);
			    		free(cmp);
			    	}
			    	else
			    	{
			    		QueueEnqueue(results,prestr);
						char lll[MAX_WORD_LENGTH];
						sprintf(lll, "%d", strlen(prestr));
						QueueEnqueue(results,lll);
			    		QueueEnqueue_front(mid,cmp);
			    		QueueEnqueue(mid,prestr);
			    		int l=mid->length;
			    		for(int k=0;k<l;k++)
			    		{
			    			char*y=QueueDequeue(mid);
			    			QueueEnqueue_front(pre,y);
			    			free(y);
			    		}
			    		free(cmp);
			    		break;
			    	}
			    }
			    else
			    {
			    	QueueEnqueue_front(mid,cmp);
			    	free(cmp);
			    }
			}
		}
	    free(str);
	}
	return(results);
}
