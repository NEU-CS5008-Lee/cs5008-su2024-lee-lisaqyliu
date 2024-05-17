/*C Program to read and print the n employee details using structure and dynamic memory allocation*/
#include <stdio.h>
#include <stdlib.h>
/*structure to hold the details of an employee*/
typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;
/* Read the employee details using scanf*/
void readData(int n, employee_t* s)
{
    // Add your code here
    for (int i = 0; i < n; i++)
    {
        printf("Enter the Employee ID, Name, Designation and  Department of Employee %d: ", i + 1);
        scanf("%d %s %s %s", &s[i].empId, s[i].Name, s[i].Designation, s[i].Dept);
    }
}
/* Function to print the employee details*/
void display(int n, employee_t * s)
{
    // Add your code here
    for (int i = 0; i < n; i++)
    {
        printf("Employee ID: %d\n", s[i].empId);
        printf("Employee Name: %s\n", s[i].Name);
        printf("Employee Designation: %s\n", s[i].Designation);
        printf("Employee Department: %s\n", s[i].Dept);
    }
}

/*----------Main Program--------*/
int main()

{
    // Main Function to print the employee details
    // Add your code here
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);
    employee_t* employee = (employee_t*)malloc(n * sizeof(employee_t)); 
    if (employee == NULL)
    {
        printf("Memory not allocated.\n");
        return 1;
    }
    readData(n, employee);
    display(n, employee);
    free(employee);
    return 0;

}

