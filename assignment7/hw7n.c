// name: Qingyang Liu
// email: liu.qingyan@northeastern.edu

// Hash table with doubly linked list for chaning/
#include <stdio.h>
#include <stdlib.h> 

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 10; 

// node struct
struct node {

    // Add your code here
    int key;
    int value;
    struct node* next;
    struct node* prev;

};

// bucket struct
struct bucket{

    // Add your code here
    struct node* head;

};

// create a new node
struct node* createNode(int key, int value){

    // Add your code here
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
  

    return newNode;
}

//  hash function with %
int hashFunction(int key){
    return key % BUCKET_SIZE;
}

//  insert a new key
void add(int key, int value){
    int hashIndex = hashFunction(key);
    
    // Add your code here
    struct node* newNode = createNode(key, value);

    if (hashTable[hashIndex].head == NULL) {
        hashTable[hashIndex].head = newNode;
    } else {
        struct node* temp = hashTable[hashIndex].head;
        while (temp->next != NULL) {
        temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
  }

}

// remove a key
void remove_key(int key){
    int hashIndex = hashFunction(key);

    // Add your code here
    struct node* temp = hashTable[hashIndex].head;
    while (temp != NULL) {
        if (temp->key == key) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                hashTable[hashIndex].head = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            free(temp);
            return;
        }
        temp = temp->next;
  }

}

// search a value using a key
void search(int key){
    int hashIndex = hashFunction(key);
    struct node* temp = hashTable[hashIndex].head;

    // Add your code here
    while (temp != NULL) {
        if (temp->key == key) {
            printf("key: %d, value: %d\n", temp->key, temp->value);
            return;
        }
        temp = temp->next;
    }
    printf("key not found\n");

    

}

void display(){
    struct node* iterator;

    printf("\n========= display start ========= \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(key: %d, val: %d)  <-> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}

int main(){
    hashTable = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));
    
    add(0, 1);
    add(1, 10);
    add(11, 12);
    add(21, 14);
    add(31, 16);
    add(5, 18);
    add(7, 19);

    display();

    remove_key(31);
    remove_key(11);

    display();

    search(11);
    search(1);
}
