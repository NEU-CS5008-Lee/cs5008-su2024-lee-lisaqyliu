// name: Qingyang Liu
// email: liu.qingyan@northeastern.edu


// please start with a copy of your hw7.c, rename it to hw.8
// and then complete the assignment
// format of document is a bunch of data lines beginning with an integer (rank which we ignore)
// then a ',' followed by a double-quoted string (city name)
// then a ',' followed by a double-quoted string (population) - ignore commas and covert to int; or (X) - convert to 0
// then a lot of entries that are ignored


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define TABLE_SIZE 400

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

//Node for linked list in hash table
typedef struct Node {
  char city[MAXSTRING];
  int population;
  struct Node* next;
} Node;

//Hash table
typedef struct {
    Node* table[TABLE_SIZE];
} HashTable;

// Function declarations
void initHashTable(HashTable* ht);
Node* createNode(char* city, int population);
void insertHashTable(HashTable* ht, int hashIndex, char* city, int population);
int hashFunction1(char* str);
int hashFunction2(char* str);
int hashFunction3(char* str);
bool isDigit(char c);
void appendChar(char* s, char c);

//Initialize hash table
void initHashTable(HashTable* ht) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    ht->table[i] = NULL;
  }
}

//Create a new node
Node* createNode(char* city, int population) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->city, city);
  newNode->population = population;
  newNode->next = NULL;
  return newNode;
}

//Insert a node into hash table
void insertHashTable(HashTable* ht, int hashIndex, char* city, int population) {
  Node* newNode = createNode(city, population);
  newNode->next = ht->table[hashIndex];
  ht->table[hashIndex] = newNode;
}

//Hash functions
int hashFunction1(char* str){
    return strlen(str) % TABLE_SIZE;
}

int hashFunction2(char* str){
    int sum = 0;
    while (*str){
        sum += *str;
        str++;
    }
    return sum % TABLE_SIZE;
}

int hashFunction3(char* str){
    if (strlen(str)<2){
        return str[0] % TABLE_SIZE;
    }
    return (str[0] * str[1]) % TABLE_SIZE;
}



// check if a character c is a digit
bool isDigit(char c) {
  if ('0' <= c && c <= '9') {
    return true;
  } else {
    return false;
  }
}

// append character c to string s
void appendChar(char* s, char c) {
    char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}



int main () {

  char inputLine[MAXSTRING];   // temporary string to hold input line
  char cityStr[MAXSTRING];     // city name
  int  lineNum;                // line number (city rank)
  int  popInt;                 // population
  int  state;                  // FSM state
  int  nextChar;               // index of next character in input string
  char temp[MAXSTRING];        // temp string to build up extracted strings from input characters
  
 
  FILE* fp;
  fp = fopen("pop.csv","r");

  HashTable ht1, ht2, ht3;
  initHashTable(&ht1);
  initHashTable(&ht2);
  initHashTable(&ht3);

  if (fp != NULL) {
    fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

    // ***** BEGIN FINTITE STATE MACHINE *****
    
    // STARTSTATE: digit -> S1
    // S1: digit -> S1; , -> S2
    // S2: " -> S3
    // S3: !" -> S3; " -> S4
    // S4: , -> S5
    // S5: " -> S6; ( -> ACCEPTSTATE
    // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE; 
    // ACCEPTSTATE: done!
    // else go to ERRORSTATE
    //
    while (feof(fp) == 0){

      nextChar = 0;
      state = STARTSTATE; 
      strcpy(temp,"");       // temp = ""

      if (nextChar >= strlen(inputLine)){
	    // if no input string then go to ERRORSTATE
	    state = ERRORSTATE;
      } 

      while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
	    switch (state) {
	    case STARTSTATE:
	        // look a digit to confirm a valid line
	        if (isDigit(inputLine[nextChar])) {
	            state = S1;
	            appendChar(temp, inputLine[nextChar]);
	        } else {
	            state = ERRORSTATE;
	        }  
	        break;


	    // ADD YOUR CODE HERE
        case S1:
            //digit -> S1; , -> S2
            if (isDigit(inputLine[nextChar])) {
                appendChar(temp, inputLine[nextChar]);
            } else if (inputLine[nextChar] == ',') {
                state = S2;
                lineNum = atoi(temp);  // convert rank to integer
                strcpy(temp, "");      // reset temp for next field
            } else {
                state = ERRORSTATE;
            }
            break;
    
        case S2:
            // " -> S3
            if (inputLine[nextChar] == '"') {
                state = S3;
            } else {
                state = ERRORSTATE;
            }
            break;

        case S3:
            // ! -> S3; " -> S4
            if (inputLine[nextChar] != '"') {
                appendChar(temp, inputLine[nextChar]);
            } else {
                state = S4;
                strcpy(cityStr, temp); // store city name
                strcpy(temp, "");      // reset temp for next field
            }
            break;

        case S4:
            // , -> S5
            if (inputLine[nextChar] == ',') {
                state = S5;
            } else {
                state = ERRORSTATE;
            }
            break;

        case S5:
            // " -> S6; ( -> ACCEPTSTATE
            if (inputLine[nextChar] == '"') {
                state = S6;
            } else if (inputLine[nextChar] == '(') {
                state = ACCEPTSTATE;
                popInt = 0;  // set population to 0 for (X)
            } else {
                state = ERRORSTATE;
            }
            break;

        case S6:
            // digit -> S6; , -> S6; " -> ACCEPTSTATE
            if (isDigit(inputLine[nextChar])) {
                appendChar(temp, inputLine[nextChar]);
            } else if (inputLine[nextChar] == ',' || inputLine[nextChar] == ' ') {
                // ignore commas and spaces within population number
            } else if (inputLine[nextChar] == '"') {
                state = ACCEPTSTATE;
                popInt = atoi(temp);  // convert population to integer
            } else {
                state = ERRORSTATE;
            }
            break;
 
	    
	    case ACCEPTSTATE:
	        // nothing to do - we are done!
	        break;
	    
	    default:
	        state = ERRORSTATE;
	        break;
	    } // end switch

	    // advance input
	    nextChar++;
	
        }	// end while state machine loop

        // ***** END FINITE STATE MACHINE *****
	  

        // Insert into hash tables
        int index1 = hashFunction1(cityStr);
        int index2 = hashFunction2(cityStr);
        int index3 = hashFunction3(cityStr);

        insertHashTable(&ht1, index1, cityStr, popInt);
        insertHashTable(&ht2, index2, cityStr, popInt);
        insertHashTable(&ht3, index3, cityStr, popInt);
      

        // get next line
        fgets(inputLine, MAXSTRING, fp);
      
    } 
    

    fclose(fp);

    //Print out hash tables
    printf("\n***** HASH TABLE 1 *****\n");
    printf("=======================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = ht1.table[i];
        if (temp != NULL) {
            printf("TABLE[%d]:\n", i);
            while (temp != NULL) {
                printf("key/value: [%s] / [%d]\n", temp->city, temp->population);
                temp = temp->next;
            }
        } else {
            printf("TABLE[%d]:\n", i);
        }
    }

    printf("\n***** HASH TABLE 2 *****\n");
    printf("=======================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = ht2.table[i];
        if (temp != NULL) {
            printf("TABLE[%d]:\n", i);
            while (temp != NULL) {
                printf("key/value: [%s] / [%d]\n", temp->city, temp->population);
                temp = temp->next;
            }
        } else {
            printf("TABLE[%d]:\n", i);
        }
    }

    printf("\n***** HASH TABLE 3 *****\n");
    printf("=======================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = ht3.table[i];
        if (temp != NULL) {
            printf("TABLE[%d]:\n", i);
            while (temp != NULL) {
                printf("key/value: [%s] / [%d]\n", temp->city, temp->population);
                temp = temp->next;
            }
        } else {
            printf("TABLE[%d]:\n", i);
        }
    }
  
  } else {
    printf("File not found!\n");
  }
  
  return 0;
}
