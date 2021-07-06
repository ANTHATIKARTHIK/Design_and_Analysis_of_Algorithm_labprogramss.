#include<stdio.h>
void linearsearch(int array[],int ele,int n)
{
	int k,i,flag=0;
	for(i=0;i<n;i++)
	{
		if(ele==array[i])
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
		printf("Element found\n");
	else
		printf("Element not found\n");
}
		 
int main()
{
	int i,n,ele;
	printf(" Enter n value \n");
	scanf("%d",&n);
	int array[n];
	printf("Enter array values \n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&array[i]);
	}
	printf("Enter value to be searched \n");
	scanf("%d",&ele);
	linearsearch(array,ele,n);
		
	return 0;
}
