//liu.qingyan@northeastern.edu
//Qingyang Liu

#include<stdio.h>
#include<string.h>

int compression(char arr[], int n, char res[]){
    
    
    
    
    //insert your code here
    int count=1; //initialize the count of the first character
    int j=0; //initialize the index of the result array
    for(int i=0;i<n;i++){
        if(i < n - 1 && arr[i]==arr[i + 1]){
            count++;
        }else{ 
            //add the character to the result array
            res[j++]=arr[i];
            // Only add the count if its greater than 1
            if(count>1){
                //convert the count to a string and add it to the result array
                char str[10];
                sprintf(str,"%d",count);
                for(int k=0;str[k]!='\0';k++){
                    res[j++]=str[k];
                }
            }
            count=1;
        }
    }
    res[j]='\0'; //add the null character to the end of the result array
    return j; //return the length of the result array
    
    
    
    
    
}
 
int main()
{
    char a[]="aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r,n=strlen(a);//n is the size of input array
    r=compression(a,n,res);
    printf("length of the compressed string:%d\n",r);
    return 0;
}
