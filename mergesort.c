#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
void mergesort(int a[],int n);
void merge(int left[],int right[],int a[],int nL,int nR,int n);

void mergesort(int a[],int n)
{
	if(n<2)
	{
		return n;
	}
	int mid=n/2;
	int nL=mid;
	int nR=n-mid;
	int *left=(int*)malloc(nL*sizeof(int));
	int *right=(int*)malloc(nR*sizeof(int));
	for(int i=0;i<nL;i++)
	{
		left[i]=a[i];
	}
	for(int i=mid;i<n;i++)
	{
		right[i-mid]=a[i];
	}
	mergesort(left,nL);
	mergesort(right,nR);
	merge(left,right,a,nL,nR,n);
}
void merge(int left[],int right[],int a[],int nL,int nR,int n)
{
	int i,j,k;
	i=j=k=0;
	while(i<nL && j<nR)
	{
		if(left[i]<=right[j])
		{
			a[k]=left[i];
			i++;
			k++;
		}
		else
		{
		a[k]=right[j];
		j++;
		k++;
		}
	}
	while(i<nL)
	{
		a[k]=left[i];
		i++;
		k++;
	}
	while(j<nR)
	{
		a[k]=right[j];
		j++;
		k++;
	}
}
int main()
{
	float time_spent=0.0;
	clock_t begin=clock();
	int n;
	printf("Enter the length of array:");
	scanf("%d",&n);
	int *a=(int*)malloc(n*sizeof(int));
	printf("Enter the elements to be sorted:\n");
	for(int i=0;i<n;i++)
	{
		printf("Element:");
		scanf("%d",&a[i]);
	}
	mergesort(a,n);
	printf("\nThe Sorted order of elements:\n");
	for(int i=0;i<n;i++)
	{
		printf("%d ",a[i]);
	}
	clock_t end=clock();
	time_spent=(float)(end-begin)/CLOCKS_PER_SEC;
	printf("\nTime Elapsed: %f",time_spent);
	return 0;
}
