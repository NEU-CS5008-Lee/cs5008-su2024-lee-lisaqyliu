//Qingyang Liu
//liu.qingyan@northeastern.edu
//To perform insertion sort of integers stored in a file and display the output and store it in another file.
#include <stdio.h>
#include<stdlib.h>

#define MAX 10

int main()
{
    FILE *fp;
    int arr[10],temp;
    int count=0,i,j;
    /*count will have the total number of elements in the array*/

    /*read the file*/
    fp=fopen("Input1.txt","r");
    if(fp==NULL){
        //if file returns NULL then can't open the file
        printf("\n Cannot open the file \n");
        exit(0);
    }
    
    //insert your code here
    
    // read integers from the file and store in the array
    while(fscanf(fp,"%d",&temp)!=EOF && count < 10){ //read the file till the end of file
        arr[count]=temp; //store the integers in the array
        count++; //increment the count
    }
    fclose(fp); //close the file

    //insertion sort
    for(i=1;i<count;i++){
        temp=arr[i]; //store the element in temp
        j=i-1; //store the previous element in j
        while(j>=0 && arr[j]>temp){
            arr[j+1]=arr[j]; //swap the elements
            j=j-1; //decrement j
        }
        arr[j+1]=temp; //store the element in the array
    }

    // open the file 
    fp=fopen("Sorted.txt","w");
    if(fp==NULL){
        //if file returns NULL then can't open the file
        printf("\n Cannot open the file \n");
        exit(0);
    }

    //write the sorted array to the file
    for (i=0;i<count;i++){
        fprintf(fp,"%d\n",arr[i]);
    }
    fclose(fp); //close the file

    //print the sorted array
    printf("\n The sorted array is \n");
    for(i=0;i<count;i++){
        printf("%d\n",arr[i]);
    }

    return 0;
}
