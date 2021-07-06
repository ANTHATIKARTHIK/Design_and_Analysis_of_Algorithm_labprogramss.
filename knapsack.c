#include<stdio.h>
#include<time.h>
#include<unistd.h>
void knapsack(int n,float weight[],float profit[],float capacity)
{
	float x[20],tp=0;
	int i,j,u;
	u=capacity;
	for(i=0;i<n;i++)
		x[i]=0.0;
	for(i=0;i<n;i++)
	{
		if(weight[i]>u) 
		{
			break;
		}
		else
		{
			x[i]=1.0;
			tp=tp+profit[i];
			u=u-weight[i];
		}
	}
	if(i<n)
	{
		x[i]=u/weight[i];
	}
	tp=tp+(x[i]*profit[i]);
	printf("\nThe result vector is:\n");
	for(i=0;i<n;i++)
		printf("x[%d]=%.2f\n",i,x[i]);
	printf("\nThe Maximum Profit is %f",tp);
}
int main()
{
	float time_spent=0.0;
	clock_t begin=clock();
	float weight[20],profit[20],capacity;
	int num,i,j;
	float ratio[20],temp;
	printf("\nEnter the no of objects:-");
	scanf("%d",&num);
	printf("\nEnter the weights and profits of each object:-\n");
	for(i=0;i<num;i++)
	{
		printf("Weight and Profit:");
		scanf("%f %f",&weight[i],&profit[i]);
	}
	printf("Enter the capacity of knapsack:");
	scanf("%f",&capacity);
	for(i=0;i<num;i++)
	{
		ratio[i]=profit[i]/weight[i];
	}
	for(i=0;i<num;i++)
	{
		for(j=i+1;j<num;j++)
		{
			if(ratio[i]<ratio[j])
			{
				temp=ratio[j];
				ratio[j]=ratio[i];
				ratio[i]=temp;
				
				temp=weight[j];
				weight[j]=weight[i];
				weight[i]=temp;
				
				temp=profit[j];
				profit[j]=profit[i];
				profit[i]=temp;
			}
		}
	}
	knapsack(num,weight,profit,capacity);
	clock_t end=clock();
	time_spent+=(float)(end-begin)/CLOCKS_PER_SEC;
	printf("\nTime Elapsed: %f",time_spent);
	return 0;
}
			