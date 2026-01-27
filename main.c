#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void addNotes();
void viewNotes();
void clearNotes();

int main() {
    int choice = 0;
    printf("---------- Cnote ----------");
   
    do {
        printf("\n1. Add note\n2. View notes\n3. Clear notes\n4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNotes();
                break;
            case 2:
                viewNotes();
                break;
            case 3:
                clearNotes();
                break;
            case 4:
                printf("\nHave a nice day! :D\n");
                return 0;
            default:
                printf("\nInvalid choice\n");
                return 0;
        }

    }while (choice < 4 && choice > 0);

    return 0;
}

void addNotes() {
    char note[100];
    char answer = '\0';
    FILE *file = fopen("notes.txt", "r");

    if (file == NULL) {
        printf("\nNo notes file exist, would you like to create one? (Y/n): ");
        scanf(" %c", &answer);
        
        if (answer == 'y' || answer == 'Y') {
            file = fopen("notes.txt", "a");
            printf("Successfully created notes.txt\n");
            fclose(file);
        }
        else if (answer == 'n' || answer == 'N') {
            printf("Creation of notes file canceled\n");
            return;
        } else {
            exit(EXIT_FAILURE);
        }
    }

    file = fopen("notes.txt", "a");
    printf("Enter your note: ");
    getchar();
    fgets(note, sizeof(note), stdin);

    time_t now = time(NULL);
    char *date = ctime(&now);
    date[strlen(date) - 1] = '\0';

    fprintf(file, "[%s] %s", date, note);
    fclose(file);
    printf("Note saved!\n");
}

void viewNotes() {
    char ch;
    FILE *file = fopen("notes.txt", "r"); 
    char answer = '\0';

    if (file == NULL) {
        printf("No note file found, would you like to create one? (Y/n): ");
        scanf(" %c", &answer);
        
        if (answer == 'y' || answer == 'Y') {
            file = fopen("notes.txt", "w");
            printf("Successfully created notes.txt!\n");
            fclose(file);
        }
        else if (answer == 'n' || answer == 'N') {
            printf("Creation of notes.txt cancled\n");
        } else {
            printf("Invalid answer\n");
        }

        return;
    }
    
    printf("\n--- Your Saved Notes ---\n");
    while ((ch=fgetc(file)) != EOF) {
        putchar(ch);
    }
    
    fclose(file);
}

void clearNotes() {
    char answer = '\0';

    printf("\n--- Clearing Notes ---\n");
    printf("WARNING! This will remove all saved notes\n");
    printf("Are you sure you'd like to do this? (Y/n): ");
    scanf(" %c", &answer);

    if (answer == 'y' || answer == 'Y') {
        FILE *file = fopen("notes.txt", "w");
        fclose(file);
        printf("Clearing complete!");
    }
    else if (answer == 'n' || answer == 'N') {
        printf("Clearing cancelled\n");
    } else {
        printf("Invalid answer");
        return;
    }
}
