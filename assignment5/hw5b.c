// name: Qingyang Liu
// email: liu.qingyan@northeastern.edu


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LIMIT 200
#define RAND_RANGE 95  // 95 printing characters x20-x7E

// return random character
char randChar() {
  // 0 -> x20 -> ' '
  // 1 -> x21 -> '!'
  // ,,,
  // 94 -> x7E -> '~'
  // see https://ascii.cl
  return ((char)((rand() % RAND_RANGE)+0x20));
}

// return the value of a char unless it is lower case
// in which case return the upper case of the character
char upperChar(char c){
  if ((c<'a') || (c>'z')){
    return(c);
  } else {
    // if you forget the displacement of lower to upper case
    // just let the computer figure it out for you!
    return(c-('a'-'A'));
  }
}



// pick pivot and then sort small and big parts 
void quicky(char* data, int left, int right) {

  // ADD YOUR CODE HERE

  if (left < right){
    char pivot = upperChar(data[right]); // pivot is the last element
    int i = left - 1; // i is the index of the smaller element

    for (int j = left; j < right; j++) { // partition the array
        if (upperChar(data[j]) <= pivot) {
            i++;
            char temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    char temp = data[i + 1]; // swap data[i + 1] and data[right]
    data[i + 1] = data[right]; // put pivot in the correct position
    data[right] = temp; 
    int partition = i + 1; // partition is the index of the pivot
    quicky(data, left, partition - 1); // sort the left side
    quicky(data, partition + 1, right); // sort the right side

  }

}



int main(){

  char source[LIMIT]; // array to hold input data values

  int i;             // loop variable
  int j;             // loop variable


  //seed random numbers
  srand((unsigned)time(NULL));

  //initialize source array with random character
  for (i=0; i<LIMIT; i++) {
    source[i] = randChar();
  }

  //print out source array in rows of 20 elments
  printf("Source array:\n");
  for (i=0; i < ((LIMIT/20)+1); i++) {
    for (j=0; j<20; j++) {
      if (i*20+j < LIMIT) {
	printf("%c ",source[i*20+j]);
      }
    }
    printf("\n");
  }
  printf("\n");

  // do the sorting
  quicky(source, 0, LIMIT-1);

  
  //print out sorted array in rows of 10
  printf("Destination array:\n");
  for (i=0; i < ((LIMIT/10)+1); i++) {
    for (j=0; j<10; j++) {
      if (i*10+j < LIMIT) {
	printf("%c ",source[i*10+j]);
      }
    }
    printf("\n");
  }
  printf("\n");
  
  return 0;
}
