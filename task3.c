//
//  main.c
//  Lab 10 Task 3
//
//  Created by Sibtaintahir512 on 11/18/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define totalrecipes 40
#define length 30
int  loadrecipes(char receipename[][length] )
{
    FILE *fptr;
    fptr = fopen("text.txt", "r");
    int count=0;
    if (fptr == NULL)
    {
        printf("File Not Found! \n");
        return 0;
    }
    else
    {
        while ( count < totalrecipes && fgets(receipename[count], length, fptr))
        {
            
            receipename[count][strcspn(receipename[count], "\n")] = '\0';
            
            
            count++;
        }
        fclose(fptr);
    }
    return count;
}
int searchrecipe(char recipesname[][length],int count)
{
    char name[length];
    printf("Enter The resipe To Search : ");
    fgets(name, length, stdin);
    
    name[strcspn(name, "\n")]='\0';

    
    printf("1.Search By full Name \n");
    printf("2.Search By Partial Name \n");
    int choice;
    printf("Enter Your Choice : ");
    scanf("%d",&choice);
    getchar();
    switch (choice) {
        case 1:
            for (int i=0; i < count; i++)
            {
                if (strcmp(recipesname[i], name)==0)
                {
                    return i;
                }
            }
            break;
        case 2:
            for (int i=0; i < count ;i++)
            {
                       if (strstr(recipesname[i], name) != NULL)
                       {
                           return i;
                       }
            }
            break;
        default:
            break;
    }
    printf("Record not Found! \n");
    return -1;
}


void addrecipe(char recipename[][length],int *count)
{
    if (*count >= totalrecipes) {
        printf("List Is Full\n");
        return;
    }
        char name[length];
        printf("Enter Recipe Name to Add : ");
        fgets(name, length, stdin);
    
        name[strcspn(name,"\n")]='\0';
    
    
        strcpy(recipename[*count], name);
        (*count)++;
        printf("Recipe Added \n");
}
void Save( char recipename[][length],int count)
{
    FILE *fptr;
    fptr = fopen("text.txt", "w");
    if (fptr == NULL)
    {
        printf("File Not Found!\n");
        return;
    }
    else
    {
        for (int i=0; i<count-1; i++)
        {
            for (int  j = i+1; j < count; j++)
            {
                if (strcmp(recipename[i],recipename[j])<0)
                {
                    char temp[length];
                    strcpy(temp,recipename[i]);
                    strcpy(recipename[i],recipename[j]);
                    strcpy(recipename[j],temp);
                }
                
            }
        }
        for (int i = 0; i < count; i++)
        {
            fprintf(fptr,"%s\n" ,recipename[i]);
        }
        
        fclose(fptr);
    }
}


void update(char recipesname[][length],int count)
{
    int index = searchrecipe(recipesname, count);
    if (index==-1)
    {
        return;
    }
    char name[length];
    printf("Enter New Recipe name : ");
    fgets(name, length, stdin);
    name[strcspn(name, "\n")]='\0';
    strcpy(recipesname[index], name);
    
}


void deleterecipe(char recipename[][length], int *count)
{
    int index = searchrecipe(recipename,*count);
    if (index == -1)
    {
       printf("Recipe Not Found! \n");
       return;
    }
    for (int i = 0; i < *count-1; i++)
    {
       strcpy(recipename[index],recipename[index+1]);
    }
    (*count)--;
    printf("Recipe Deleted \n");
}
int main(int argc, const char * argv[]) {
    char recipename[totalrecipes][length];
    int count=0;
    int choice;
    int c;
    int index;
    while (1){
        printf("1.Load Recipes\n");
        printf("2.Add Recipes\n");
        printf("3.Update Recipe\n");
        printf("4.Search recipe\n");
        printf("5.Save and Exit\n ");
        printf("6.Delete Recipe \n");
        printf("------------------------------\n");
        printf("Enter Your Choice : ");
        scanf("%d",&choice);
        getchar();
        switch (choice) {
            case 1:
               count = loadrecipes(recipename);
                printf("Recipes Loaded Successfully \n");
                printf("------------------------------\n");
                break;
            case 2:addrecipe(recipename, &count);
                printf("Recipes Added Successfully \n");
                printf("------------------------------\n");
                break;
            case 3:
                update(recipename, count);
                printf("Recipes Updated Successfully \n");
                printf("------------------------------\n");
                break;
            case 4:
                index = searchrecipe(recipename,count);
                if (index!=-1)
                {
                   printf("Your Recipe  Found (%s) at index %d \n",recipename[index],index);
                }
                
            case 5:
                Save(recipename,count);
                return 0;
            case 6:
                deleterecipe(recipename,&count);
                break;
            default:
                break;
        }
    }
   
    return EXIT_SUCCESS;
}
