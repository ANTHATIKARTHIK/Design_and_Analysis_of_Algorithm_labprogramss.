#include <stdio.h>
int max(int a, int b)
{
    if(a>b)
	return a;
    else
	return b;
}
int knapSack(int W, int wt[], int val[], int n)
{
    int i, w;
    int K[n + 1][W + 1];
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]],K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    i=n;
    int k=W;
    while(i>0 && k>0)
    {
    	if(K[i][k]!=K[i-1][k])
	{
		printf("Item %d(weight %d) is included completely\n",i,wt[i-1]);
		i=i-1;
		k=k-wt[i];
	}
	else
	{
		i=i-1;
	}
    }
    printf("Total Profit is:%d",K[n][W]);
}
int main()
{
	int n,W;
	printf("Enter number of items:");
	scanf("%d",&n);
	printf("\nEnter maximum capacity of knapsack:");
	scanf("%d",&W);
	int value[n],wt[n];
	for(int i=0;i<n;i++)
	{
		printf("\nEnter weight of item %d:",i+1);
		scanf("%d",&wt[i]);
		printf("\nEnter value of item %d:",i+1);
		scanf("%d",&value[i]);
	}
	knapSack(W, wt, value, n);
        return 0;
}