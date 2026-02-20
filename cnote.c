#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "flags.h"

int main(int argc, char **argv) {
    int opt = 0;
    
    while ((opt = getopt(argc, argv, "a:vc")) != -1) {
        switch (opt) {
            case 'a':
                flagAdd(optarg);
                break;
            case 'v':
                flagView();
                break;
                return 0;
            case 'c':
                flagClear();
                break;
        }
        return 0;
    }
    return 0;
}
