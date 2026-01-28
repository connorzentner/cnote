#include <stdio.h>
#include <time.h>
#include <string.h>

#define CLEAR_SCREEN() printf("\033[2J\033[H")
#define RESET_COLOR()  printf("\033[0m")
#define BORDER_COLOR() printf("\033[38;5;8m")
#define GOTO_XY(x, y) printf("\033[%d;%dH", (y), (x))

#define BOX_W 60
#define BOX_H 10

void addNotes();
void viewNotes();
void clearNotes();
void drawBorder(int width, int height, const char* title);
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice = 0;

    do {
        CLEAR_SCREEN();
        drawBorder(BOX_W, BOX_H, "Cnote");

        viewNotes();

        GOTO_XY(1, BOX_H + 3);
        printf("[1]Add note   [2]Refresh notes   [3]Clear notes    [4]Exit\n");
        printf("\nChoice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                addNotes();
                break;
            case 2:
                break;
            case 3:
                clearNotes();
                break;
            case 4:
                GOTO_XY(1, BOX_H + 5);
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
    GOTO_XY(1, BOX_H + 6);
    
    char note[100];
    FILE *file = fopen("notes.txt", "a");
    
    printf("Enter your note: ");
    fgets(note, sizeof(note), stdin);

    time_t now = time(NULL);
    char *date = ctime(&now);
    date[strlen(date) - 1] = '\0';

    fprintf(file, "[%s] %s", date, note);
    fclose(file);
    printf("Note saved!\n(Press Enter)");
    getchar();
}

void viewNotes() {
    FILE *file = fopen("notes.txt", "r");
    if (file == NULL) {
        GOTO_XY(3, 3);
        printf("(No notes found)");
        return;
    }

    char line[256];
    int row = 3;
    
    while (fgets(line, sizeof(line), file) && row < (BOX_H + 1)) {
        GOTO_XY(3, row);
        line[strcspn(line, "\n")] = 0;
        printf("%.55s", line);
        row++;
    }
    
    fclose(file);
}

void clearNotes() {
    GOTO_XY(1, BOX_H + 6);
    char answer;
    printf("Clear all notes? (y/n): ");
    scanf(" %c", &answer);

    if (answer == 'y' || answer == 'Y') {
        FILE *file = fopen("notes.txt", "w");
        fclose(file);
        printf("Notes cleared!");
    }
    getchar();
}

void drawBorder(int width, int height, const char* title) {
    int title_len = (int)strlen(title);
    BORDER_COLOR();

    GOTO_XY(1, 1);
    printf("┌─%s", title);
    for (int i = 0; i < (width - title_len - 3); i++) printf("─");
    printf("┐");

    for (int i = 0; i < height; i++) {
        GOTO_XY(1, i + 2);
        printf("│");
        GOTO_XY(width, i + 2);
        printf("│");
    }

    GOTO_XY(1, height + 2);
    printf("└");
    for (int i = 0; i < width - 2; i++) printf("─");
    printf("┘");
    RESET_COLOR();
}
