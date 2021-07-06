#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#include<string.h>
//#include<limits.h>
#define MAX 99999999
#define N 20
int final_path[11]; //final_path[] stores the path of the travelling salesman 

bool visited[11];

int final_res = MAX; //Stores the final minimum cost of shortest tour 

void copyToFinal(int curr_path[], int n) //Copying temporary solution to the final solution 
{
	int i;
	for (i=0; i<n; i++)
		final_path[i] = curr_path[i];
	final_path[N] = curr_path[0];
}

int firstMin(int adj[N][N], int i, int n)  //Function to find the minimum edge cost 
{
	int k;
	int min = MAX;
	for (k=0; k<n; k++)
		if (adj[i][k]<min && i != k)
			min = adj[i][k];
	return min;
}

int secondMin(int adj[N][N], int i, int n) //function to find the second minimum edge cost
{
	int j;
	int first = MAX;
	int second = MAX;
	for (j=0; j<n; j++)
	{
		if (i == j)
			continue;

		if (adj[i][j] <= first)
		{
			second = first;
			first = adj[i][j];
		}
		else if (adj[i][j] <= second && adj[i][j] != first)
			second = adj[i][j];
	}
	return second;
}

void TSPRec(int adj[N][N], int curr_bound, int curr_weight,int level, int curr_path[], int n)
{
	int i,j;
	if (level==n)
	{
		if (adj[curr_path[level-1]][curr_path[0]] != 0)
		{
			int curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];
			if (curr_res < final_res)
			{
				copyToFinal(curr_path, n);
				final_res = curr_res;
			}
		}
		return;
	}
	for (i=0; i<n; i++)
	{
		if (adj[curr_path[level-1]][i] != 0 && visited[i] == false)
		{
			int temp = curr_bound;
			curr_weight += adj[curr_path[level-1]][i];
			if (level==1)
			curr_bound -= ((firstMin(adj, curr_path[level-1], n) + firstMin(adj, i,n))/2);
			else
			curr_bound -= ((secondMin(adj, curr_path[level-1], n) + firstMin(adj, i, n))/2);
			if (curr_bound + curr_weight < final_res)
			{
				curr_path[level] = i;
				visited[i] = true;

				TSPRec(adj, curr_bound, curr_weight, level+1, curr_path, n); 
			}
			curr_weight -= adj[curr_path[level-1]][i];
			curr_bound = temp;

			memset(visited, false, sizeof(visited));
			for (j=0; j<=level-1; j++)
				visited[curr_path[j]] = true;
		}
	}
}

void TSP(int adj[N][N], int n)
{
	int i;
	int curr_path[n+1];
	int curr_bound = 0;
	memset(curr_path, -1, sizeof(curr_path));
	memset(visited, 0, sizeof(curr_path));

	for (i=0; i<n; i++)
		curr_bound += (firstMin(adj, i, n) + secondMin(adj, i, n));

	curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2;

	visited[0] = true;
	curr_path[0] = 0;

	TSPRec(adj, curr_bound, 0, 1, curr_path, n);
}

int main()
{
	int n;
	int adj[N][N];
	printf("\n Enter no of vertices: ");
	scanf("%d", &n);
	int i, j;
	printf("\n");
	printf("Enter cost matrix:\n");
	for (i = 0; i<n; i++){
		//printf(" ");
	    	for (j = 0; j<n; j++){
	        	scanf("%d", &adj[i][j]);
	    }
	}

	TSP(adj,n);

	printf("\n Minimum cost for TSP tour is: %d\n", final_res);
	printf("\n Path Taken is: ");
	for (i=0; i<n; i++)
		printf("%d --> ", final_path[i]);
	printf("%d",final_path[i]);

	return 0;
}

