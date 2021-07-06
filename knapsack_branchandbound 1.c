//Program to implement 0/1 knapsack problem using branch and bound
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#define min(a,b) a<b?a:b;
int size;
int knapsack_weight;
bool * global_best;
int global_lb;
int global_lb_2;
typedef struct Item
{
	int profit; 
	int weight; 
	int idx;
}Item;
typedef struct Node
{
	int upper_bound;
	int lower_bound;
	int level;
	bool flag;
	int cp;
	int cw;
}Node;
typedef struct priority_queue
{
	Node *array;
	int queue_size;
}priority_queue;

priority_queue* create_queue()
{
	priority_queue* p = (priority_queue*)malloc(sizeof(priority_queue));
	p->array=(Node*)malloc(sizeof(Node)*1000);
	p->queue_size=0;
	return p;
}
void swap(Node *a, Node *b)
{
	Node temp=*a;
	*a=*b;
	*b=temp;
}
void heapify(priority_queue* p, int idx)
{
	int left=2*idx+1;
	int right=2*idx+2;
	int smallest=idx;
	if(left<p->queue_size && p->array[smallest].lower_bound>=p->array[left].lower_bound)
		smallest=left;
	if(right<p->queue_size && p->array[smallest].lower_bound>=p->array[right].lower_bound)
		smallest=right;
	if(smallest!=idx)
	{
		swap(&p->array[smallest],&p->array[idx]);
		heapify(p,smallest);
	}
}
void insert(priority_queue* p, Node element)
{
	p->queue_size++;
	int idx=p->queue_size-1;
	while(idx>0 && element.lower_bound>=p->array[(idx-1)/2].lower_bound)
	{
		p->array[idx]=p->array[(idx-1)/2];
		idx=(idx-1)/2;
	}
	p->array[idx]=element;
}
void remove_(priority_queue* p)
{
	swap(&p->array[0],&p->array[p->queue_size-1]);
	p->queue_size--;
	heapify(p,0);
}
void sort(Item * arr)
{
	int i,j;
	for(i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			if((double)arr[i].profit/arr[i].weight<(double)arr[j].profit/arr[j].weight)
			{
				Item temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
int calculate_upper_bound(int cp,int cw,int idx, Item* arr)
{
	int profit=cp;
	int weight=cw,i;
	for(i=idx;i<size;i++)
	{
		if(weight+arr[i].weight<=knapsack_weight)
		{
			weight+=arr[i].weight;
			profit-=arr[i].profit;
		}
		else
		{
			profit-=(double)(knapsack_weight-weight)/arr[i].weight*arr[i].profit;
			break;
		}
	}
	return profit;
}
int calculate_lower_bound(int cp,int cw, int idx, Item* arr)
{
	int profit=cp;
	int weight=cw;
	int i;
	for(i=idx;i<size;i++)
	{
		if(weight+arr[i].weight<=knapsack_weight)
		{
			weight+=arr[i].weight;
			profit-=arr[i].profit;
		}
		else
		{
			break;
		}
	}
	return profit;
}
void knapsack(Item* arr)
{
	sort(arr);
	priority_queue* p=create_queue();
	Node current,left,right;
	current.upper_bound=current.lower_bound=0;
	current.cp=current.cw=0;
	current.level=current.flag=0;
	bool select[size];
	int i;
	global_best=(bool*)malloc(sizeof(bool)*(size+1));
	for(i=0;i<size;i++)
		select[i]=false;
	insert(p,current);
	
	while(p->queue_size !=0)
	{
		current=p->array[0];
		remove_(p);
		if((current.upper_bound> global_lb || current.upper_bound>global_lb_2) && current.level!=0)
			continue;
		if(current.level!=0)
		{
			select[current.level-1]=current.flag;
		}
		if(current.level==size)
		{
			if(current.lower_bound < global_lb_2)
			{
				for(i=0;i<size;i++)
				{
					global_best[arr[i].idx]=select[i];
				}
			}
			global_lb_2=min(global_lb_2,current.lower_bound);
			continue;
		}
		right.upper_bound=calculate_upper_bound(current.cp,current.cw,current.level+1,arr);
		right.lower_bound=calculate_lower_bound(current.cp,current.cw,current.level+1,arr);
		right.flag=false;
		right.level=current.level+1;
		right.cp=current.cp;
		right.cw=current.cw;
		global_lb=min(global_lb,right.lower_bound);
		if(current.cw+arr[current.level].weight<=knapsack_weight)
		{
			left.upper_bound=calculate_upper_bound(current.cp-arr[current.level].profit,current.cw+arr[current.level].weight,current.level+1,arr);
			left.lower_bound=calculate_lower_bound(current.cp-arr[current.level].profit,current.cw+arr[current.level].weight,current.level+1,arr);
			left.flag=true;
			left.level=current.level+1;
			left.cw=current.cw+arr[current.level].weight;
			left.cp=current.cp-arr[current.level].profit;
			global_lb=min(global_lb,left.lower_bound);
		}
		else
		{
			left.lower_bound=left.upper_bound=0;
			left.level++;
		}
		if(right.upper_bound <= global_lb && global_lb !=0) insert(p,right);
		if(left.upper_bound<=global_lb && global_lb!=0) insert(p,left);
	}
	printf("The elements taken into the knapsack are(The resultant vector is):\n");
	for(i=0;i<size;i++)
	{
		//global_best[i]==0? printf("0 "): printf("1 ");
		if(global_best[i]==0)
			printf("0 ");
		else
			printf("1 ");
	        printf(" ");
	}
	float profit=abs(global_lb_2);
	printf("\nMaximum profit is:%f",profit);
	free(p->array);
	free(global_best);
}
int main()
{
	int i;
	printf("Enter the number of items:\n");
	scanf("%d",&size);
	Item arr[size];
	for(i=0;i<size;i++)
	{
		printf("Enter weight and profit of Item %d:\n",i+1);
		scanf("%d %d",&arr[i].weight,&arr[i].profit);
		arr[i].idx=i;
	}
	printf("Enter the knapsack capacity:");
	scanf("%d",&knapsack_weight);
	global_lb=0;
	global_lb_2=0;
	knapsack(arr);
	return 0;
}
