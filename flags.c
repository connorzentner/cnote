#include <stdio.h>
#include <time.h>
#include <string.h>

#include "flags.h"

void flagAdd(char *flag) {
    char note[100];

    if (flag != NULL) {
        strncpy(note, flag, sizeof(note) - 1);
        FILE *file = fopen("notes.txt", "a");
        if (file) {
            time_t now = time(NULL);
            char *date = ctime(&now);
            date[strlen(date) - 1] = '\0';
            fprintf(file, "[%s] %s\n", date, note);

            fclose(file);
            printf("Note saved via command line!\n");
        }
    }
}

void flagView() {
    FILE *file = fopen("notes.txt", "r");
    if (!file) {
        printf("notes.txt found.\n");
        return;
    }
    int text = fgetc(file);
    if (text == EOF) {
        printf("No notes taken.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void flagClear() {
    FILE *file = fopen("notes.txt", "w");
    if (!file) {
        printf("No notes to clear.\n");
    } else {
        printf("Notes cleared via command line!\n");
    }
    fclose(file);
}
