#include<stdio.h>
#define INFINITY 99999999
int min(int a,int b);
void floydwarshall(int p[150][150],int n) 
{
	int i,j,k;
	for (k=1;k<=n;k++)
	{
	  for (i=1;i<=n;i++)
	  {
	   for (j=1;j<=n;j++)
	   {
			if(i==j)
				p[i][j]=0; 
			else
				p[i][j]=min(p[i][j],p[i][k]+p[k][j]);
	   }
	  }
	}
}
int min(int a,int b) 
{
	if(a<b)
		return a;
	else
		return b;
}
int main() 
{
	int G[150][150];
	int n,i,j;
	printf("Enter number of vertices:");
	scanf("%d",&n);
	printf("Enter the adjacency matrix:");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%d",&G[i][j]);
		}
	}
	floydwarshall(G,n);
	printf("\n All pairs shortest paths are:\n");
	for (i=1;i<=n;i++)
	{
	  for (j=1;j<=n;j++)
	  {
		    printf("\n (%d,%d)=%d",i,j,G[i][j]);
	  }
	}
	return 0;
}



