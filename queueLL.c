#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
struct queue {
    struct node *front, *rear;
};
int count = 0;
void enqueue(struct queue *q, int num) {
    struct node *newnode, *p;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode -> data = num;
    newnode -> next = NULL;
    if ( ! q -> rear ) {
        q -> front  = newnode;
        q -> rear = newnode;
        ++ count;
    }
    else {
        q -> rear -> next = newnode;
        q -> rear = newnode;
        ++ count;
    }
    printf("Enqueued!\n");
}
int dequeue(struct queue *q) {
    if (! q -> front) {
        return -1;
    }
    int num = q -> front -> data;
    q -> front = q -> front -> next;
    -- count;
    return num;
}
int peek(struct queue *q) {
    if (! q -> front) {
        return -1;
    }
    return q -> front -> data;
}
void display(struct queue *q) {
    struct node *p;
    p = (struct node *)malloc(sizeof(struct node));
    p = q -> front;
    if ( ! p) {
        printf("No elements to display\n");
    }
    else {
        printf("The elements of the queue are:\n");
        while ( p != NULL) {
            printf("%d ", p -> data);
            p = p -> next;
        }
        printf("\n");
    }
}
int main() {
    struct queue *q;
    q = (struct queue *)malloc(sizeof(struct queue));
    q -> rear = q -> front = NULL;
    int ch, num;
    printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\nPlease enter your choice:\n");
    scanf("%d", &ch);
    while ( ch != 5) {
        switch (ch) {
            case 1: printf("Enter the number to be enqueued: ");
                    scanf("%d", &num);
                    enqueue(q, num);
                    break;
            case 2: num = dequeue(q);
                    if ( num == -1) {
                        printf("No elements in the queue to delete\n");
                    }
                    else  {
                        printf("%d is dequeued from the queue\n", num);
                    }
                    break;
            case 3: num = peek(q);
                    if ( num == -1) {
                        printf("No elements in the queue\n");
                    }
                    else  {
                        printf("%d is the top element of the queue\n", num);
                    }
                    break;
            case 4: display(q);
                    break;
            case 5: printf("Exiting\n");
                    break;
        }
        printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\nPlease enter your choice:\n");
        scanf("%d", &ch);
    }
    return 0;
}