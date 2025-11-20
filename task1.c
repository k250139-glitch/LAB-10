//
//  main.c
//  LAB task 10
//
//  Created by Sibtaintahir512 on 11/14/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define maxtitles 10
#define length 100

int searchtitle(char title[][length],int count)
{
    char name[length];
    printf("Enter The title To Search : ");
    fgets(name, length, stdin);
    
    name[strcspn(name, "\n")]='\0';
    
    for (int i=0; i < count; i++)
    {
        if (strcmp(title[i], name)==0)
        {
            return i;
        }
    }
    return -1;
}


void mydelete(char titles[][length], int *count)
{
    int index = searchtitle(titles,*count);
    if (index == -1)
    {
       printf("title Not Found! \n");
       return;
    }
    for (int i = 0; i < *count-1; i++)
    {
       strcpy(titles[index],titles[index+1]);
    }
    (*count)--;
    printf("Title Deleted \n-----------------------------------\n");
}
void update(char title[][length],int count)
{
    int index = searchtitle(title, count);
    if (index==-1)
    {
        return;
    }
    char name[length];
    printf("Enter New Title name : ");
    fgets(name, length, stdin);
    name[strcspn(name, "\n")]='\0';
    strcpy(title[index], name);
    
}
void Save( char title[][length],int count)
{
    FILE *fptr;
    fptr = fopen("title.txt", "w");
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
                if (strcmp(title[i],title[j])>0)
                {
                    char temp[length];
                    strcpy(temp,title[i]);
                    strcpy(title[i],title[j]);
                    strcpy(title[j],temp);
                }
                
            }
        }
        for (int i = 0; i < count; i++)
        {
            fprintf(fptr,"%s\n" ,title[i]);
        }
        
        fclose(fptr);
    }
}

void addtitle(char title[][length],int *count)
{
    if (*count >= maxtitles) {
        printf("List Is Full\n");
        return;
    }
        char name[length];
        printf("Enter title Name to Add : ");
        fgets(name, length, stdin);
    
        name[strcspn(name,"\n")]='\0';
    
    
        strcpy(title[*count], name);
        (*count)++;
        printf("Title Added \n");
}


int  loadtitles(char title[][length] )
{
    FILE *fptr;
    fptr = fopen("title.txt", "r");
    int count=0;
    if (fptr == NULL)
    {
        printf("File Not Found! \n");
        return 0;
    }
    else
    {
        while ( count < maxtitles && fgets(title[count], length, fptr))
        {
            
            title[count][strcspn(title[count], "\n")] = '\0';
            
            
            count++;
        }
        fclose(fptr);
    }
    return count;
}

int main(int argc, const char * argv[])
{
    char title[maxtitles][length];
        int count=0;
        int choice;
        int c;
        int index;
        while (1){
            printf("1.Load Title\n");
            printf("2.Add Title\n");
            printf("3.Update Title\n");
            printf("4.Search title\n");
            printf("5.Save and Exit\n ");
            printf("6.Delete Title \n");
            printf("------------------------------\n");
            printf("Enter Your Choice : ");
            scanf("%d",&choice);
            getchar();
            switch (choice) {
                case 1:
                   count = loadtitles(title);
                    printf("Title Loaded Successfully \n");
                    printf("------------------------------\n");
                    break;
                case 2:addtitle(title, &count);
                    printf("Title Added Successfully \n");
                    printf("------------------------------\n");
                    break;
                case 3:
                    update(title, count);
                    printf("Title Updated Successfully \n");
                    printf("------------------------------\n");
                    break;
                case 4:
                    index = searchtitle(title,count);
                    if (index!=-1)
                    {
                       printf("Your Title  Found (%s) at index %d \n",title[index],index);
                    }
                    
                case 5:
                    Save(title,count);
                    return 0;
                case 6:
                    mydelete(title,&count);
                    break;
                default:
                    break;
            }
        }
       
    return EXIT_SUCCESS;
}
