#include<stdio.h>
int binarysearch(int array[],int ele,int n)
{
	int first=0,last=n,mid;
	
	while(first<=last)
	{
		mid=(first+last)/2;
		if(array[mid]==ele)
			return mid;
		if(ele>array[mid])
			first=mid+1;
		if(ele<array[mid])
			last=mid-1;
	}
       return -1;
}
int main()
{
	int i,n,ele;
	printf("Enter n value \n");
	scanf("%d",&n);
	int array[n];
	printf("Enter array values in sorted order  \n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&array[i]);
	}
	printf("Enter value to be searched \n");
	scanf("%d",&ele);
	int p=binarysearch(array,ele,n);
	if(p!=-1)
		printf("Element found\n");
	else
		printf("Element not found\n");	
	return 0;
}
