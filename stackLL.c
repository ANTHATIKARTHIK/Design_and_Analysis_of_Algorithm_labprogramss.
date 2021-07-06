#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
struct stack {
    struct node* top;
};
int count = 0;
void push( struct stack *s, int num) {
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode -> data = num;
    newnode -> next = NULL;
    if ( s -> top ) {
        newnode -> next = s -> top;
    }
    s -> top = newnode;
    ++ count;
    printf("Pushed %d into the stack!\n", num);
}
int pop(struct stack *s) {
    if (!s -> top) {
        return -1;
    }
    int num = s -> top -> data;
    s -> top = s -> top -> next;
    -- count;
    return num;
}
void display(struct stack *s) {
    if ( ! s -> top) {
        printf("No elements to display\n");
    }
    else {
        struct node *p;
        p = (struct node *)malloc(sizeof(struct node));
        p = s -> top;
        printf("The elements in the stack are:\n ");
        while ( p != NULL) {
            printf("%d ", p -> data);
            p = p -> next;
        }
        printf("\n");
    }
}
int main() {
    struct stack* s;
    s = (struct stack *)malloc(sizeof(struct stack));
    s -> top = NULL;
    printf("1. Push \n2. Pop\n3. Peek\n4. Display\n5. Exit\nEnter your choice: ");
    int ch, num;
    scanf("%d", &ch);
    while ( ch != 5) {
        switch (ch) {
            case 1: printf("Enter the number to be pushed: ");
                    scanf("%d", &num);
                    push(s, num);
                    break;
            case 2: num = pop(s);
                    if ( num == -1) {
                        printf("No elements to delete\n");
                    }
                    else  {
                        printf("%d is poped from the stack\n", num);
                    }
                    break;
            case 3: if ( s -> top == NULL) {
                        printf("The stack is empty\n");
                    }
                    else {
                        printf("%d is the top element\n", s -> top -> data);
                    }
                    break;
            case 4: display(s);
                    break;
            case 5: printf("Exiting\n");
                    break;
        }
        printf("1. Push\n2. Pop\n3. Peek\n4. Display \n5. Exit\nEnter your choice: ");
        scanf("%d", &ch);
    }
    return 0;
}   
 