#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#define BOX_W 60
#define BOX_H 10

void addNotes();
void viewNotes();
void clearNotes();

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int choice = 0;
    do {
        clear();

        attron(A_DIM);
        border(0,0,0,0,0,0,0,0);
        mvprintw(0, 40, " Cnote ");
        attroff(A_DIM);

        viewNotes();

        mvprintw(BOX_H + 5, 1, "[1]Add [2]Refresh [3]Clear [4]Exit");
        mvprintw(BOX_H + 10, 1, "Choice: ");
        refresh();

        echo();
        char input[10];
        getnstr(input, sizeof(input) - 1);
        noecho();

        choice = atoi(input);

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
                printf("Closing...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }while (choice < 4 && choice > 0);

    endwin();
    return 0;
}

void viewNotes() {
    FILE *file = fopen("notes.txt", "r");
    if (!file) {
        mvprintw(2, 5, "No notes found...");
        return;
    }

    char line[200];
    int row = 5;
    
    while (fgets(line, sizeof(line), file) && row < BOX_H) {
        line[strcspn(line, "\n")] = 0;
        mvprintw(row++, 1, "%.55s", line);
    }
    fclose(file);
}

void addNotes() {
    echo();
    curs_set(1);
    char note[100];

    mvprintw(BOX_H + 6, 1, "Enter note: ");
    getnstr(note, sizeof(note) - 1);

    FILE *file = fopen("notes.txt", "a");
    if (file) {
        time_t now = time(NULL);
        char *date = ctime(&now);
        date[strlen(date) - 1] = '\0';
        fprintf(file, "[%s] %s\n", date, note);
        fclose(file);
    }

    mvprintw(BOX_H + 7, 1, "Saved! [press any key]");
    noecho();
    curs_set(0);
    getch();
}

void clearNotes() {
    mvprintw(BOX_H + 6, 1, "Clear all notes? [y/n]: ");
    int ch = getch();
    if (ch == 'y' || ch == 'Y') {
        FILE *file = fopen("notes.txt", "w");
        if (file) fclose(file);
        mvprintw(BOX_H + 7, 1, "Cleared! [press any key]");
    }
    getch();
}
