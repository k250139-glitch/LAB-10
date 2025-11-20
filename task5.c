#include<stdio.h>
#include<string.h>

#define length 100
#define maxwords 20

int wordcount(char name[]){

    int count = 0;
   for(int i=0; name[i]!='\0' ; i++)
   {
    if (name[i]==' ' || name[i]=='.' || name[i]=='\t' || name[i]=='?' || name[i]==',')
    {
        count++;
        while (i + 1 < length && name[i + 1] == ' ')
                {
                    i++;
                }
    }
    
    
   }
   return count;
}



int loadTag(char phrase[][length])
{
    FILE *fptr;
    fptr = fopen("tags.txt","r");
    if (fptr==NULL)
    {
        printf("File Not Found \n");
        return 0;
    }
    int count = 0;
    while (count < maxwords && fgets(phrase[count],length,fptr))
    {

        phrase[count][strcspn(phrase[count],"\n")]='\0';

        (count)++;
    }

    fclose(fptr);

    return count;

}

void addTag(char phrase[][length], int *count)
{
    char name[length];
    printf("Enter Phrase to Add: ");
    fgets(name,length,stdin);


    name[strcspn(name,"\n")]='\0';


    if (wordcount(name)>7)
    {
       printf("Words Limit Exceeded \n");
       return;
    }
    
    strcpy(phrase[*count],name);
    (*count)++;

}


int searchTag(char phrase[][length], int count)
{
    char name[length];
    printf("Enter Phrase to Search: ");
    fgets(name,length,stdin);
    name[strcspn(name,"\n")]='\0';

    for (int i = 0; i < count; i++)
    {
        if (strcmp(phrase[i],name)==0)
        {
           return i;
        }
        
    }
    return -1;
}


void updateTag(char phrase[][length], int count)
{
    int index = searchTag(phrase,count);
    if (index==-1)
    {
        printf("No Such phrase Found! \n");
        return;
    }

    char name[length];
    printf("Enter Phrase to update : ");
    fgets(name,length,stdin);
    name[strcspn(name,"\n")]='\0';

    if (wordcount(name)>7)
    {
        printf("Words Limit Exceeded! \n");
        return;
    }
    
    strcpy(phrase[index],name);

}

void saveTag(char phrase[][length], int count)
{
    FILE *fptr;
    fptr = fopen("tags.txt","w");
    if (fptr==NULL)
    {
        printf("File Not Found! \n");
        return;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            fprintf(fptr,"%s\n",phrase[i]);
        }
        fclose(fptr);
    }
}

void deleteTag(char phrase[][length], int *count)
{
    int index = searchTag(phrase,*count);
    if (index==-1)
    {
        printf("No Such Phrase Found! \n");
        return;
    }

    for (int i = index; i < (*count)-1; i++)
    {
        strcpy(phrase[i],phrase[i+1]);
    }
    (*count)--;

}

void displayTag(char phrase[][length], int count) {
    if (count == 0) {
        printf("No tags available.\n");
        return;
    }

    printf("\n--- Saved Tags ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, phrase[i]);
    }
}


int main(void)
{

char tags[maxwords][length];
    int count = loadTag(tags);
    int choice;

    do {
        printf("\n--- PHOTO TAG MANAGER ---\n");
        printf("1. Display all tags\n");
        printf("2. Add a new tag\n");
        printf("3. Delete a tag\n");
        printf("4. Update a tag\n");
        printf("5. Search tags\n");
        printf("6. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: displayTag(tags, count); break;
            case 2: addTag(tags, &count); break;
            case 3: deleteTag(tags, &count); break;
            case 4: updateTag(tags, count); break;
            case 5: searchTag(tags, count); break;
            case 6: saveTag(tags, count); break;
            default: printf("Invalid option.\n");
        }
    } while(choice != 0);

    return 0;
}
