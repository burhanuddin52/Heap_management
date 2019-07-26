#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 1000
typedef struct allocate_node
{
	// char object[5];
	int object;
	int address;
	int sizedata;
	struct allocate_node*next;
}allocatenode;

typedef struct free_node
{
	int address;
	int sizedata;
	struct free_node*next;
}freenode;
 
 typedef enum{success,failure
 }statuscode;
 
void initialise(freenode**fptr)
{
	freenode*ptr;
	ptr=(freenode*)malloc(sizeof(freenode));
	ptr->address=0;
	ptr->sizedata=SIZE;
	ptr->next=NULL;
	*fptr=ptr;
}
allocatenode *sptr;
int allocation(allocatenode**aptr,freenode**fptr,int n)
{
	allocatenode *nptr,*prev;
	freenode *lptr,*prev1;
	lptr=*fptr;
	sptr=*aptr;
	nptr=*aptr;
    prev1=*fptr;
	while(lptr!=NULL && lptr->sizedata<n)
	{
		prev1=lptr;
		lptr=lptr->next;
	}
	if(lptr==NULL)
	{
		return -1;
	}
	else
	{
		sptr=(allocatenode*)malloc(sizeof(allocatenode));
		sptr->address=lptr->address;
		sptr->sizedata=n;
		sptr->next=NULL;
		if(lptr->address==0)
		{
			sptr->object=0;
		}
		else
		{
			sptr->object=lptr->address;
		}
		if(*aptr==NULL)
		{
			*aptr=sptr;
		}
		else
		{
			if( nptr->address<sptr->address)
			{
				while(nptr!=NULL)
				{
					prev=nptr;
					nptr=nptr->next;
				}
				prev->next=sptr;
				sptr->next=nptr;
			}
		}
		

		if(lptr->sizedata==n)
		{
			if(prev1==lptr)
			{
				*fptr=lptr->next;
			}
			else
			{
				prev1->next=lptr->next;
			}
			
			if(*fptr==NULL)
			{
				printf("Free list is empty\n");
			}
		}
		else
		{
		lptr->address=lptr->address+n;
		lptr->sizedata=lptr->sizedata-n;
		}
	}
	return (sptr->object);
}

statuscode freeing(allocatenode**aptr,freenode**fptr,int l)//char y[])
{
	allocatenode*nptr;
	nptr=*aptr;
	statuscode sc=success;
	allocatenode*prev;
	freenode*lptr,*ptr;
	lptr=*fptr;
	freenode*prev1;
	int flag=0;
	int n;
	prev=*aptr;
	prev1=*fptr;

	if(nptr==NULL)
	{
		sc=failure;
	}
	else
	{
		if(nptr->object==l)
		{
			nptr=*aptr;
			*aptr=nptr->next;
			flag=1;
		}
		while(nptr!=NULL && flag==0)
		{
			if(nptr->object==l)//(strcmp(nptr->object,y)==0)
			{
				flag=1;
			}
			else
			{
				prev=nptr;
				nptr=nptr->next;
			}
		}
	if(flag==0)
	{
		printf("No such object exists\n");
	}
	else
	{
		if(*fptr==NULL)
		{
			freenode*smptr;
			smptr=(freenode*)malloc(sizeof(freenode));
			smptr->address=nptr->address;
			smptr->sizedata=nptr->sizedata;
			smptr->next=NULL;
			prev->next=nptr->next;
			free(nptr);
			*fptr=smptr;
		}
		else
		{
			prev->next=nptr->next;
			ptr=(freenode*)malloc(sizeof(freenode));
			ptr->address=nptr->address;
			ptr->sizedata=nptr->sizedata;
			free(nptr);
			if(ptr->address<lptr->address)
			{
				ptr->next=lptr;
				*fptr=ptr;
			}
			else
			{
				while(lptr!=NULL && ptr->address>lptr->address)
				{
					prev1=lptr;
					lptr=lptr->next;
				}
				prev1->next=ptr;
				ptr->next=lptr;
			}
			freenode*sptr,*cptr,*dptr;
			sptr=*fptr;
			cptr=sptr->next;
			while(sptr!=NULL)
			{
				while(cptr!=NULL && sptr->address+sptr->sizedata==cptr->address)
				{
					sptr->sizedata=sptr->sizedata+cptr->sizedata;
					dptr=cptr;
					cptr=cptr->next;
					sptr->next=cptr;
					free(dptr);
				}
				sptr=sptr->next;
			}
		}
	}
	}
	return sc;
}

void printPhysicalDist(allocatenode*aptr,freenode*fptr)
{
	allocatenode *nptr1=aptr;
		allocatenode* prev=NULL;
	freenode*nptr2=fptr;
	freenode*cptr=fptr;
	freenode*dptr,*sptr;
	printf("\nAllocated Physical memory looks like\n");
	while(nptr1!=NULL)
	{
		printf("Chunk Size: ");
		printf("%d\n",nptr1->sizedata);
		printf("Physical Address Allocated: ");
		printf("%d",nptr1->address);
		printf("....");
		printf("%d\n",(nptr1->sizedata+nptr1->address-1));
		
		
		nptr1=nptr1->next;
		// prev=nptr1->next;

	}
	// printf("");
	printf("Unallocated Physical memory is: ");

	while(nptr2!=NULL)
	{
		printf("%d",nptr2->address);
		printf("....");
		printf("%d  ",nptr2->sizedata);
		nptr2=nptr2->next;
	}
	printf("\n");
	printf("\n");
}
void printPhysicalDist1(allocatenode*aptr,freenode*fptr)
{
	allocatenode *nptr1=aptr;
	freenode*nptr2=fptr;
	freenode*cptr=fptr;
	freenode*dptr,*sptr;
	// printf("Unallocated Physical meory is\n");
	printf("\n");
	
	while(nptr1!=NULL)
	{
		printf("Logical Start Address: ");
		printf("\nAllocated Physical memory is\n");
		printf("%d\n",nptr1->object);
		printf("Chunk Size: ");
		printf("%d\n",nptr1->sizedata);
		printf("Physical Address Allocated: ");
		printf("%d",nptr1->address);
		printf("....");
		// printf("Sizedata %d",nptr1->sizedata);
		printf("%d\n",(nptr1->sizedata+nptr1->address-1));
		nptr1=nptr1->next;
	}
	// printf("");
	printf("Unallocated Physical memory is: ");

	while(nptr2!=NULL)
	{
		printf("%d",nptr2->address);
		printf("....");
		printf("%d  ",nptr2->sizedata);
		nptr2=nptr2->next;
	}
	printf("\n");
	printf("\n");
}
main()
{
	freenode*fptr;
	int x;
	// char obj[5],y[5];
	int y;
	int r;
	statuscode sc;
	allocatenode*aptr;
	aptr=NULL;
	initialise(&fptr);
	int option;
	printf("Enter the option number\n");
	printf("Enter 1 for allocation\n");
	printf("Enter 2 for freeing\n");
	printf("Enter 3 for exit\n");
	int flag=0;
	while(flag==0)
	{
		scanf("%d",&option);
	switch(option)
		{
			case 1:
			// printf("Enter the name ");
			// scanf("%s",&obj);	
			printf("Enter the data size required: ");
			scanf("%d",&x);
			r=allocation(&aptr,&fptr,x);
			printf("\n");
			printf("Logical Start Address is:");
			printf("%d",r);
			if(r>=0)//sc==success)
			{
				printPhysicalDist(aptr,fptr);
			}
			else
			{
				printf("Couldn't allocate");
			}
		
			break;
			
			case 2: printf("Enter the Logical Start Adresss block to be freed \n");
			scanf("%d",&y);
			sc=freeing(&aptr,&fptr,y);
			if(sc==success)
			{
			printPhysicalDist1(aptr,fptr);
			}
			else
			{
				printf("Nothing left to free");
				
				}	
			break;
			
			case 3: flag=1;
		}
	}
}
