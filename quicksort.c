#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
void quicksort(int arr[],int start,int end);
int partition(int arr[],int start,int end);

void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void quicksort(int arr[],int start,int end)
{
	int pos;
	if(start<end)
	{
		pos=partition(arr,start,end);
		quicksort(arr,start,pos-1);
		quicksort(arr,pos+1,end);
	}
}

int partition(int arr[],int start,int end)
{
	int pivot=arr[end];
	int PIndex=start;
	for(int i=start;i<end;i++)
	{
		if(arr[i]<=pivot)
		{
			swap(&arr[i],&arr[PIndex]);
			PIndex=PIndex+1;
		}
	}
	swap(&arr[PIndex],&arr[end]);
	return PIndex;
}
		
int main()
{
	float time_spent=0.0;
	clock_t begin=clock();
	int n,i;
	printf("Enter the length of array:");
	scanf("%d",&n);
	int *arr=(int*)malloc(n*sizeof(int));
	printf("E nter the elements in array:\n");
	for(i=0;i<n;i++)
	{
		printf("Element:");
		scanf("%d",&arr[i]);
	}
	quicksort(arr,0,n-1);
	printf("The Sorted array:\n");
	for(int i=0;i<n;i++)
	{
		printf("%d ",arr[i]);
	}
	clock_t end=clock();
	time_spent=(float)(end-begin)/CLOCKS_PER_SEC;
	printf("\nTime Elapsed: %f",time_spent);
	return 0;
}
	
