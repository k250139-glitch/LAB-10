#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define maxaffrim 100
#define length 100


int  loadaffirm( char affrim[][length] ,int *count )
{
    FILE *fptr;
    fptr = fopen("affrim.txt","r");
    if (fptr == NULL)
    {
        printf("File Not Found! \n");
        return 0;
    }
    while (*count < maxaffrim && fgets(affrim[*count],length,fptr))
    {
        
        affrim[*count][strcspn(affrim[*count],"\n")]='\0';

        if (strlen(affrim[*count])>0)
        (*count)++;
    }
    fclose(fptr);

    return *count;
    
}




int wordcount(char *affrim)
{
    int count=0;
   for (int  i = 0; i < length; i++)
    {
        if (affrim[i]==' ' || affrim[i]== '.' || affrim[i]== '\t' || affrim[i]==',' || affrim[i]=='?')
        {
           count++;
           while (i + 1 < length && affrim[i + 1] == ' ')
                {
                    i++;
                }
        }
    }
    return count;
}



void addnew(char affrim[][length], int *count)
{
    if (*count >= maxaffrim)
    {
        printf("List Ful! \n");
        return;
    }
    char name[length];
    printf("Enter A new Phrase: ");
    fgets(name,length,stdin);

    name[strcspn(name,"\n")]='\0';


    if (wordcount(name)>=7)
    {
        printf("Maximum Words limit Exceeded! \n");
        return;
    }

    strcpy(affrim[*count],name);
    (*count)++;
    
    printf("Phrase(Affrimation) Added \n");
}

 


int searchaffrim(char affrim[][length], int count)
{
    char name[length];
    printf("Enter A new Phrase to search : ");
    fgets(name,length,stdin);

    name[strcspn(name,"\n")]='\0';

    for (int  i = 0; i < count; i++)
    {
        if (strcmp(affrim[i],name)==0)
        {
            return i;
        }
        
    }
    return -1;
}



void updateaffrim(char affrim[][length] , int count)
{
    int index = searchaffrim(affrim,count);
    if (index==-1)
    {
        printf("NO such Phrase Found \n");
        return;
    }
    char name[length];
    printf("Enter new affrimation: ");
    fgets(name,length,stdin);

    name[strcspn(name,"\n")]='\0';
    
    if (wordcount(name)>=7)
    {
       printf("Word Limit exceeded \n");
       return;
    }

    strcpy(affrim[index],name);
    printf("Affrimation updated Succesfully \n");
    
}



void deleteaffrim(char affrim[][length], int *count)
{
    int index = searchaffrim(affrim,*count);
    if (index==-1)
    {
        printf("Affrimation not Found to Delete ");
        return;
    }
    for (int  i = 0; i < *count-1; i++)
    {
        strcpy(affrim[i],affrim[i+1]);
    }
    
    (*count)--;
    printf("Affrimation Deleted Successfully \n");
}


void save(char affrim[][length], int count)
{
    FILE *fptr;
    fptr = fopen("affrim.txt","w");
    if (fptr==NULL)
    {
        printf("File Not Found! \n");
        return;
    }
    for (int i = 0; i < count-1; i++)
    {
       for (int j = i+1; j < count; j++)
       {
        if (strcmp(affrim[i],affrim[j])>0)
        {
            char temp[length];
            strcpy(temp,affrim[i]);
            strcpy(affrim[i],affrim[j]);
            strcpy(affrim[j],temp);
        }
        
       }
       
    }
    
    for (int  i = 0; i < count; i++)
    {
        fprintf(fptr,"%s\n",affrim[i]);
    }
    
}
int main(void)
{
    char affrim[maxaffrim][length];
    int count = 0;
    int choice=0;
    int index=0;
    while (1)
    {
        printf("1.Load Affrimation\n");
        printf("2.Add Affrimation\n");
        printf("3.Update Affrimation\n");
        printf("4.Search Affrimation\n");
        printf("5.Delete Affrimation\n ");
        printf("6.Save and Exit \n");
        printf("------------------------------\n");
        printf("Enter Your Choice:");
        scanf("%d",&choice);
        getchar();

        printf("------------------------------\n");
        switch (choice)
        {
        case 1:
            loadaffirm(affrim,&count);
            printf("------------------------------\n");
            break;
        case 2:
            addnew(affrim,&count);
            printf("------------------------------\n");
            break;
        case 3:
            updateaffrim(affrim,count);
            printf("------------------------------\n");
        case 4:
            index = searchaffrim(affrim,count);
            if (index!=-1)
            {
              printf("Affrimation Found at index %d \n ",index);
              printf("------------------------------\n");
            }
            if (index==-1)
            {
                printf("Affirmation Not Found \n");
                printf("------------------------------\n");
            }
            
            break;
        case 5:
            deleteaffrim(affrim,&count);
            printf("------------------------------\n");
            break;
        case 6:
            save(affrim,count);
            return 0;
        default:
            break;
        }
    }
    
}
