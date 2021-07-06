#include <stdio.h>
#include <stdlib.h>

#define HASHVALUE(key) (key % 11);
/* To get hash value of a given key */

typedef struct node{
    int val;
    struct node *next;
}node;

node **hashTable;
/* declaring a global hashtable */

int createHashTable() {
    for (int i = 0; i < 11; ++ i) {
        hashTable[i] = (node *)malloc(sizeof(node));
        hashTable[i] -> val = 0;
        hashTable[i] -> next = NULL;
    }
}
/* initializing heads of hashtable buckets */

void insertAt(int val, int key) {
    if (hashTable[key] -> val == 0) {
        hashTable[key] -> val = val;
        hashTable[key] -> next = NULL;
    }
    else {
        node *p = hashTable[key];
        while (p -> next) {
            p = p -> next;
        }
        node *newNode = (node *)malloc(sizeof(node));
        newNode -> val = val;
        newNode -> next = NULL;
        p -> next = newNode;
    }
}
/* inserting a given key value pair into hashtable */

void insertAll(int inputArray[20], int size) {
    int key, hashval;
    for (int index = 0; index < size; ++ index ) {
        key = inputArray[index];
        hashval = HASHVALUE(key);
        insertAt(key, hashval );
    }
}
/* inserting a given array of elements into hashtable */

int hashSearch(int searchVal) {
    int hashval = HASHVALUE(searchVal);
    node *p = hashTable[hashval];
    while (p) {
        if ( p -> val == searchVal ) {
            return 1;
        }
        p = p -> next;
    }
    return 0;
}
/* to search if a value is present in the hashtable or not */

void displayBucket(int key) {
    node *p = hashTable[key];
    printf("Bucket %d: ", key);
    while (p -> next) {
        printf("%d -> ", p -> val);
        p = p -> next;
    }
    printf("%d\n", p -> val);
}
/* to display a specific bucket of the hashtable */

void displayTable() {
    for (int index = 0; index < 11; ++ index) {
        displayBucket(index);
    }
}
/* displaying entire hashtable */

int main() {
    hashTable = (node **)malloc(11 * sizeof(node *));
    createHashTable();
    int arr[] = {1, 2, 13, 4, 5, 3, 63, 7, 8, 88, 120};
    insertAll(arr, 11);
    displayTable();
    if (hashSearch(13)) {
        printf("Found in hashtable\n");
    }
    else {
        printf("Not found in hashtable\n");
    }
    return 0;
}