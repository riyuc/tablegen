#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE* writeFile(char* fileName) {
    srand(time(NULL)); // Initialize random seed
    FILE* file = fopen(strcat(fileName, ".csv"), "w");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }
    return file;
}
FILE* readFile(char* fileName){
    //something
    FILE* file = fopen(fileName, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }
    return file;
}
