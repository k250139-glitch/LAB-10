//
//  main.c
//  LAB 10 Task 2
//
//  Created by Sibtaintahir512 on 11/17/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define maxlevels 100
#define length 200

int wordcount(const char *str)
{
    int count = 0 ;
    int inword = 0 ;
    for (int i=0; str[i]!='\0'; i++)
    {
        if (str[i] !=' ' && !inword)
        {
            inword =1;
            count++;
        }
        else if (str[i]==' ')
        {
            inword = 0;
        }
    }
    return count;
}


int loadlevels(char level[][length])
{
    FILE *fptr;
    fptr = fopen("levels.txt", "r");
    int count = 0;
    if (fptr == NULL)
    {
        printf("File Not Found! \n");
        return count;
    }
    else{
        while (count < maxlevels && fgets(level[count], length, fptr)) {
            level[count][strcspn(level[count], "\n")] = '\0';
            count++;
        }
        fclose(fptr);
    }
    return count;
}


void savelevels(char level[][length],int count)
{
    FILE *fptr;
    fptr = fopen("levels.txt", "w");
    if (fptr == NULL )
    {
        printf("File Not Found! \n");
        return ;
    }
    else {
        for (int i=0; i< count; i++)
        {
            fprintf(fptr,"%s\n",level[i]);
        }
        fclose(fptr);
    }
}


void addlevel(char level[][length], int *count){
    if (*count >= maxlevels)
    {
        printf("List Full \n");
        return;
    }
    char temp[length];
    printf("Enter new Level description: ");
    fgets(temp, length, stdin);
    temp[strcspn(temp, "\n")]='\0';
    
    if (wordcount(temp)>7)
    {
        printf("Description too long \n");
        return;
    }
    strcpy(level[*count], temp);
    (*count)++;
    printf("Level Added \n");
}


int searchlevel(char level[][length], int count , const char *name ){
    for (int i=0; i<count; i++)
    {
        if (strcmp(level[i], name)==0)
        {
            return i;
        }
    }
    return -1;
}


void updatelevel(char level[][length], int count){
    char name[length];
    printf("Enter Level to update: ");
    fgets(name, length, stdin);
    name[strcspn(name, "\n")]='\0';
    int index = searchlevel(level, count, name);
    if (index==-1)
    {
        printf("Level Not Found! \n");
        return;
    }
    char newtext[length];
    printf("Enter New Description: ");
    fgets(newtext, length, stdin);
    newtext[strcspn(newtext, "\n")]='\0';
    if (wordcount(newtext)>7)
    {
        printf("Too Many Words \n");
        return;
    }
    strcpy(level[index], newtext);
    printf("Level data Updated \n");
}



void deletelevel(char level[][length] , int *count)
{
    char name[length];
    printf("Enter Level to Delete:");
    fgets(name, length, stdin);
    name[strcspn(name, "\n")]='\0';
    
    int index = searchlevel(level, *count, name);
    if (index == -1)
    {
        printf("Level Not found");
        return;
    }
    for (int i=0; i < *count-1 ; i++)
    {
        strcpy(level[index], level[i+1]);
    }
    (*count)--;
    printf("Level Deleted \n");
}



int main(int argc, const char * argv[]) {
    char level[maxlevels][length];
    int choice;
    int count = loadlevels(level);
    do {
        printf("\n--- Level Tracker Menu ---\n");
        printf("1. Add Level\n");
        printf("2. Search Level\n");
        printf("3. Update Level\n");
        printf("4. Delete Level\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        
        scanf("%d", &choice);
        getchar();
        if (choice == 1)
        {
            addlevel(level, &count);
        }
        else if (choice == 2)
        {
            char name[length];
            printf("Enter Level to search: ");
            fgets(name, length, stdin);
            name[strcspn(name, "\n")]='\0';
            int index = searchlevel(level, count, name);
            if (index != -1)
            {
                printf("Level Found At Position : %d\n",index);
            }
            else
            {
                printf("Level Not Found ");
            }
        }
        else if (choice==3)
        {
            updatelevel(level, count);
        }
        else if (choice == 4)
        {
            deletelevel(level, &count);
        }
    }while(choice!= 5);
        savelevels(level, count);
        printf("All Changes Saved \n");
    return EXIT_SUCCESS;
}
