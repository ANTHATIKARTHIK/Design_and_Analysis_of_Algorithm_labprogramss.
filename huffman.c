#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct HuffmanNode
{
	struct HuffmanNode *left,*right;
	int freq;
	char data;
}HuffmanNode;

typedef struct MinHeap
{
	int size,capacity;
	HuffmanNode **array;
}MinHeap;

void printCodes(HuffmanNode* root,int arr[],int top);
void HuffmanCodes(char data[],int freq[],int size);
HuffmanNode* buildHuffmanTree(char data[],int freq[],int size);
MinHeap* createAndBuildMinHeap(char data[],int freq[],int size);
void insertMinHeap(MinHeap* minHeap,HuffmanNode* HuffmanNode);
void buildMinHeap(MinHeap *minHeap);
void minHeapify(MinHeap *minHeap,int idx);
HuffmanNode* extractMin(MinHeap *minHeap);
void swap(HuffmanNode** a,HuffmanNode** b);

void swap(HuffmanNode** a,HuffmanNode** b)
{
	HuffmanNode *t=*a;
	*a=*b;
	*b=t;
}

int main()
{
	char arr[]={'a','b','c','d','e','f'};
	int freq[]={5,9,12,13,16,45};
	int size=sizeof(arr);
	HuffmanCodes(arr,freq,size);
}

void HuffmanCodes(char data[],int freq[],int size)
{
	HuffmanNode *root=buildHuffmanTree(data,freq,size);
	int arr[MAX],top=0;
	printCodes(root,arr,top);
}

HuffmanNode* buildHuffmanTree(char data[],int freq[],int size)
{
	HuffmanNode *left,*right,*top;
	MinHeap *minHeap=createAndBuildMinHeap(data,freq,size);
	while(minHeap->size!=1)
	{
		left=extractMin(minHeap);
		right=extractMin(minHeap);
		HuffmanNode *top=malloc(sizeof(HuffmanNode*));
		top->data='#';
		top->freq=left->freq+right->freq;
		top->left=left;
		top->right=right;
		insertMinHeap(minHeap,top);
	}
	return extractMin(minHeap);
}

MinHeap* createAndBuildMinHeap(char data[],int freq[],int size)
{
	MinHeap *minHeap=malloc(sizeof(MinHeap));
	minHeap->size=0;
	minHeap->capacity=size;
	minHeap->array=malloc(minHeap->capacity*sizeof(HuffmanNode *));
	for(int i=0;i<size;i++)
	{
		HuffmanNode *temp=malloc(sizeof(HuffmanNode*));
		temp->data=data[i];
		temp->freq=freq[i];
		temp->left=temp->right=NULL;
		minHeap->array[i]=temp;
	}
	minHeap->size=size;
	buildMinHeap(minHeap);
	return minHeap;
}

void buildMinHeap(MinHeap *minHeap)
{
	int n=minHeap->size-1;
	int i;
	for(i=(n-1)/2;i>=0;--i)
		minHeapify(minHeap,i);
}

void minHeapify(MinHeap *minHeap,int idx)
{
	int small=idx;
	int left=2*idx+1;
	int right=2*idx+2;
	if(left<minHeap->size && minHeap->array[left]->freq<minHeap->array[small]->freq)
		small=left;
	if(right<minHeap->size && minHeap->array[right]->freq<minHeap->array[small]->freq)
		small=right;
	if(small!=idx)
	{
		swap(&minHeap->array[small],&minHeap->array[idx]);
		minHeapify(minHeap,small);
	}
}

HuffmanNode* extractMin(MinHeap *minHeap)
{
	HuffmanNode *temp=minHeap->array[0];
	minHeap->array[0]=minHeap->array[minHeap->size-1];
	--minHeap->size;
	minHeapify(minHeap,0);
	return temp;
}

void insertMinHeap(MinHeap* minHeap,HuffmanNode* HuffmanNode)
{
	++minHeap->size;
	int i=minHeap->size-1;
	while(i&&HuffmanNode->freq<minHeap->array[(i-1)/2]->freq);
	{
		minHeap->array[i]=minHeap->array[(i-1)/2];
		i=(i-1)/2;
	}
	minHeap->array[i]=HuffmanNode;
}

void printCodes(HuffmanNode* root,int arr[],int top)
{
	if(root->left)
	{
		arr[top]=0;
		printCodes(root->left,arr,top+1);
	}
	if(root->right)
	{
		arr[top]=1;
		printCodes(root->right,arr,top+1);
	}
	if(root->left==NULL && root->right==NULL)
	{
		printf("%c: ",root->data);
		for(int i=0;i<top;i++)
			printf("%d",arr[i]);
		printf("\n");
	}
}