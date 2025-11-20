#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define maxnotes 200
#define length 256

int loadnotes(char notes[][length]){
    FILE *f = fopen("episodes.txt","r");
    if (!f) return 0;
    int count = 0;
    while (count < maxnotes && fgets(notes[count], length, f)){
        notes[count][strcspn(notes[count], "\n")] = '\0';
        count++;
    }
    fclose(f);
    return count;
}


int savenotes(char notes[][length], int count){
    FILE *f = fopen("episodes.txt","w");
    if (!f) {
        perror("Failed to open episodes.txt for writing");
        return 0;
    }
    for (int i = 0; i < count; ++i){
        fprintf(f, "%s\n", notes[i]);
    }
    fclose(f);
    return 1;
}

int comparetoken(const char *p, int len, const char *word){
    unsigned long int wlen = strlen(word);
    if (wlen != len) return 0;
    for (int i = 0; i < len; ++i){
        if (tolower((unsigned char)p[i]) != tolower((unsigned char)word[i])) return 0;
    }
    return 1;
}

int countwordintext(const char *text, const char *word){
    const char *p = text;
    int count = 0;
    while (*p){
        
        while (*p && !isalpha((unsigned char)*p)) p++;
        const char *start = p;
        while (*p && isalpha((unsigned char)*p)) p++;
        int len = p - start;
        if (len > 0 && comparetoken(start, len, word))
            count++;
    }
    return count;
}

int countwordallnotes(char notes[][length], int n, const char *word){
    int total = 0;
    for (int i = 0; i < n; ++i){
        total += countwordintext(notes[i], word);
    }
    return total;
}

int searchnote(char notes[][length], int n, const char *title){
    for (int i = 0; i < n; ++i){
        const char *a = notes[i];
        const char *b = title;
        while (*a && *b && *a == *b){ a++; b++; }
        if (*a == '\0' && *b == '\0') return i;
    }
    return -1;
}

void displaynotes(char notes[][length], int n){
    if (n == 0){
        puts("No notes saved.");
        return;
    }
    puts("Saved notes:");
    for (int i = 0; i < n; ++i){
        printf("%d: %s\n", i+1, notes[i]);
    }
}


void addnote(char notes[][length], int *n){
    if (*n >= maxnotes){
        puts("Note list is full.");
        return;
    }
    char buf[length];
    printf("Enter new note title: ");
    if (!fgets(buf, length, stdin)) return;
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) == 0){ puts("Empty title not added."); return; }
    strcpy(notes[*n], buf);
    (*n)++;
    puts("Note added.");
}

void removenote(char notes[][length], int *n){
    if (*n == 0){ puts("No notes to remove."); return; }
    displaynotes(notes, *n);
    printf("Enter number to remove: ");
    int idx;
    if (scanf("%d", &idx) != 1)
    { while (getchar() != '\n')
        puts("Invalid input.");
        return;
    }
    while (getchar() != '\n');
    if (idx < 1 || idx > *n){ puts("Out of range."); return; }

    for (int i = idx-1; i < (*n)-1; ++i){
        char *dst = notes[i];
        char *src = notes[i+1];
        while ((*dst++ = *src++) != '\0');
    }
    (*n)--;
    puts("Removed.");
}

void editnote(char notes[][length], int n){
    if (n == 0){ puts("No notes to edit."); return; }
    displaynotes(notes, n);
    printf("Enter number to edit: ");
    int idx;
    if (scanf("%d", &idx) != 1){
        while (getchar() != '\n')
        puts("Invalid input.");
        return;
    }
    while (getchar() != '\n');
    if (idx < 1 || idx > n){ puts("Out of range."); return; }
    char buf[length];
    printf("Enter new title: ");
    if (!fgets(buf, length, stdin)) return;
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) == 0){ puts("Empty title not saved."); return; }
    strcpy(notes[idx-1], buf);
    puts("Updated.");
}

void dosearch(char notes[][length], int n){
    char buf[length];
    printf("Enter title to search: ");
    if (!fgets(buf, length, stdin)) return;
    buf[strcspn(buf, "\n")] = '\0';
    int idx = searchnote(notes, n, buf);
    if (idx == -1) puts("Not found.");
    else printf("Found at %d: %s\n", idx+1, notes[idx]);
}

void docountword(char notes[][length], int n){
    char buf[length];
    printf("Enter word to count: ");
    if (!fgets(buf, length, stdin)) return;
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) == 0){ puts("Empty word."); return; }
    int total = countwordallnotes(notes, n, buf);
    printf("The word '%s' appears %d time(s) across %d note(s).\n", buf, total, n);
}

int main(void){
    char notes[maxnotes][length];
    int n = loadnotes(notes);
    printf("Loaded %d notes.\n", n);

    while (1){
        puts("\nMenu:\n1) List notes\n2) Add note\n3) Search note\n4) Remove note\n5) Edit note\n6) Count word across all notes\n7) Save & Exit\n8) Exit without saving");
        printf("Choose option: ");
        int opt;
        if (scanf("%d", &opt) != 1){
            while (getchar() != '\n')
            puts("Invalid choice.");
            continue; }
        while (getchar() != '\n');
        switch (opt){
            case 1: displaynotes(notes, n); break;
            case 2: addnote(notes, &n); break;
            case 3: dosearch(notes, n); break;
            case 4: removenote(notes, &n); break;
            case 5: editnote(notes, n); break;
            case 6: docountword(notes, n); break;
            case 7:
                if (savenotes(notes, n)) puts("Saved. Exiting.");
                return 0;
            case 8:
                puts("Exiting without saving.");
                return 0;
            default: puts("Unknown option.");
        }
    }
    return 0;
}

