#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <chrono>

#define ARR_SIZE 10

void printMenu();
void deleteRecord(struct Cat catRecords[ARR_SIZE], int* elements);
void addRecord(struct Cat catRecords[ARR_SIZE], int* elements);
void modifyRecord(struct Cat catRecords[ARR_SIZE], int* elements);
void getInput(struct Cat catRecords[ARR_SIZE], int* elements);
void displayRecords(struct Cat catRecords[ARR_SIZE], int* elements);

struct Cat
{   
    int ID;
    char name[51];
    char breed[51];
    int birthY;
    int age;    
};

void main()
{            
    struct Cat catRecords[ARR_SIZE];
    int elements = 0;       
    printMenu();        
    getInput(catRecords, &elements);          
}

void printMenu()
{
    system("cls");
    printf("Choose an option...or else\n1) Display Records\t2) Add Record\t3) Modify Record\t4) Delete Record\t0)Quit\n");
}

void getInput(Cat catRecords[ARR_SIZE], int* elements)
{
    int choice = 1;
        
    while (choice != 0)
    {
        while (scanf_s("%d", &choice) != 1 || choice < 0 || choice > 4)
        {
            if(choice = getchar() != '\n' && choice != EOF)
            {
                puts("Invalid operation");
            }
            else
            {
                puts("Not a valid choice");
            }
        }
        if (choice == 1)
        {
            displayRecords(catRecords, elements);
        }
        else if (choice == 2)
        {
            addRecord(catRecords, elements);
        }
        else if (choice == 3)
        {
            modifyRecord(catRecords, elements);
        }
        else if (choice == 4)
        {
            deleteRecord(catRecords, elements);
        }          
    }
    printf("Exiting program\n");
}

void displayRecords(Cat catRecords[ARR_SIZE], int* elements)
{          
    if (*elements == 0)
    {
        puts("No records to display");        
    }
    else
    {
        puts("\nID    Name       Breed          Birth Year   Age\n=================================================");
        for (int i = 0; i < *elements; i++)
        {                       
            printf("%-6d%-11s%-15s%-13d%-d\n", catRecords[i].ID, catRecords[i].name, catRecords[i].breed, catRecords[i].birthY, catRecords[i].age);                  
        }        
    }        
}


void addRecord(Cat catRecords[ARR_SIZE], int* elements)
{            
    if(*elements < ARR_SIZE)
    {
        int returnValue;
        int data = 0;
        int trash = 0;
        int loop = 0;        
        ++(*elements);
        catRecords[*elements - 1].ID = *elements;
        printf("Enter your cat's name: ");        
        getchar();
        fgets(catRecords[*elements - 1].name, 51, stdin);
        catRecords[*elements-1].name[strcspn(catRecords[*elements-1].name, "\n")] = 0;
        printf("Enter your cat's breed: ");                
        fgets(catRecords[*elements - 1].breed, 51, stdin);
        catRecords[*elements - 1].breed[strcspn(catRecords[*elements - 1].breed, "\n")] = 0;      
        printf("Enter your cat's birth year: ");       
        returnValue = scanf_s("%d", &data);
        while (returnValue != 1 || data < 0)
        {
            if (returnValue == 0)
            {
                while (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid operation");
                    getchar();
                    returnValue = scanf_s("%d", &data);
                }
            }
            else
            {
                puts("Birth year can't be negative");
                getchar();
                returnValue = scanf_s("%d", &data);
            }
        }
        catRecords[*elements - 1].birthY = data;
        printf("Enter your cat's age: ");
        getchar();
        returnValue = scanf_s("%d", &data);
        //how to get current year?        
        int currentYear = 2023;        
        while (returnValue != 1 || data < 0 || (currentYear-catRecords[*elements-1].birthY)%data > 1)
        {
            if (returnValue != 1)
            {
                while (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid operation");
                    getchar();
                    returnValue = scanf_s("%d", &data);
                }
            }           
            else if (data < 0)
            {
                puts("Age can't be negative");
                getchar();
                returnValue = scanf_s("%d", &data);
            }
            else
            {
                puts("Age is not compatible with birth year");
                //getchar();
                returnValue = scanf_s("%d", &data);
            }
        }
        catRecords[*elements - 1].age = data;       
    }
    else
    {
        char placeholder[10];
        puts("The records array is full, enter any character to return to menu");
        scanf_s("%s", placeholder, 5);
    }
    printMenu();
}

//need to check if new birth year is compatible with age
void modifyRecord(Cat catRecords[ARR_SIZE], int* elements)
{
    if (*elements != 0)
    {
        int id;
        int trash = 0;
        int returnValue;
        int data;
        printf("Enter the ID you would like to modify: ");         
        returnValue = scanf_s("%d", &id);
        while (returnValue == 0 || id > 10 || id <= 0 || id > *elements)
        {        
            if (returnValue == 0)
            {
                while (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid ID");
                    returnValue = scanf_s("%d", &id);
                }
            }
            if(id > *elements && id <= 10)
            {
                puts("No record to modify at that location");
            }
            else
            {
                printf("Not a valid ID\n");
            }                       
            returnValue = scanf_s("%d", &id);
        }       
        printf("Would you like to modify the name?  1) Yes  2) No\n");
        returnValue = scanf_s("%d", &data);        
        while (returnValue != 1 || (data != 1 && data != 2))
        {
            if(returnValue != 1)
            {
                while (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid operation");
                    returnValue = scanf_s("%d", &data);
                }
            }
            else
            {            
                puts("Not a valid choice");
                returnValue = scanf_s("%d", &data);
            }
        }        
        if (data == 1)
        {
            printf("Enter the new name: ");            
            getchar();
            fgets(catRecords[id - 1].name, 51, stdin);            
            catRecords[id - 1].name[strcspn(catRecords[id - 1].name, "\n")] = 0;
        }            

        printf("Would you like to modify the breed?  1) Yes  2) No\n");
        returnValue = scanf_s("%d", &data);
        while (returnValue != 1 || (data != 1 && data != 2))
        {
            if (returnValue != 1)
            {
                while (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid operation");
                    returnValue = scanf_s("%d", &data);
                }
            }
            else
            {
                puts("Not a valid choice");
                returnValue = scanf_s("%d", &data);
            }
        }
        if (data == 1)
        {
            printf("Enter the new breed: ");
            getchar();
            fgets(catRecords[id - 1].breed, 51, stdin);
            catRecords[id - 1].breed[strcspn(catRecords[id - 1].name, "\n")] = 0;
        }        

        printf("Would you like to modify the birth year?  1) Yes  2) No\n");
        returnValue = scanf_s("%d", &data);
        while (returnValue != 1 || (data != 1 && data != 2))
        {
            if (returnValue == 0)
            {
                while (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid operation");
                    returnValue = scanf_s("%d", &data);
                }
            }
            else
            {
                puts("Not a valid choice");
                returnValue = scanf_s("%d", &data);
            }            
        }
        if (data == 1)
        {
            printf("Enter the new birth year: ");
            returnValue = scanf_s("%d", &data);
            while (returnValue != 1 || data < 0 || ((2021 - data) % catRecords[id - 1].age) > 1)
            {
                if (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid birth year");
                }
                else if (data < 0)
                {
                    puts("Birth year can't be negative");
                }                
                else
                {
                    puts("Birth year is not compatible with age");
                }
                returnValue = scanf_s("%d", &data);
            }
            catRecords[id - 1].birthY = data;
        }

        printf("Would you like to modify the age?  1) Yes  2) No\n");
        returnValue = scanf_s("%d", &data);
        while (returnValue != 1 || (data != 1 && data != 2))
        {
            if (returnValue == 0)
            {
                while (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid operation");
                    returnValue = scanf_s("%d", &data);
                }
            }
            else
            {
                puts("Not a valid choice");
                returnValue = scanf_s("%d", &data);
            }
        }
        if (data == 1)
        {
            printf("Enter the new age: ");
            returnValue = scanf_s("%d", &data);
            while (returnValue != 1 || data < 0 || ((2021 - catRecords[id-1].birthY) % data > 1))
            {
                if (trash = getchar() != '\n' && trash != EOF)
                {
                    puts("Invalid age");                    
                }
                else if (data < 0)
                {
                    puts("Age can't be negative");                    
                }
                else
                {
                    puts("Age is not compatible with birth year");
                }
                returnValue = scanf_s("%d", &data);
            }
            catRecords[id - 1].age = data;            
        }
        printMenu();
    }
    else
    {        
        puts("There are no records to modify");
    }   
    
}               


void deleteRecord(Cat catRecords[ARR_SIZE], int *elements)
{       
    if (*elements <= 0)
    {        
        printf("There is nothing to delete\n");                               
    }    
    else
    {        
        int returnValue;
        int trash = 0;
        int id;
        printf("What is the ID of the record to delete?\n");
        returnValue = scanf_s("%d", &id);
        while (returnValue != 1 || id < 1 || id > *elements)
        {
            if (trash = getchar() != '\n' && trash != EOF || id > 10)
            {
                puts("Invalid ID");
            }
            else if (id < 1)
            {
                puts("The ID can't be less than one");
            }
            else
            {
                puts("That location is already empty");
            }
            returnValue = scanf_s("%d", &id);
        }           

        for (int i = id; i < *elements; i++)
        {            
            catRecords[i-1].birthY = catRecords[i].birthY;                        
            catRecords[i-1].age = catRecords[i].age;
            strcpy_s(catRecords[i-1].name, catRecords[i].name);   
            strcpy_s(catRecords[i - 1].breed, catRecords[i].breed);
        }
        --(*elements);
        printMenu();
    }         
}