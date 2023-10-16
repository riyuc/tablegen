#include "generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "io.h"
#include "constants.h"

// Function to generate a random number within a range.
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Generates a random User ID.
int generateUserID() {
    return randomInRange(1000, 9999); // Example range
}

// Generates a random first name. (This is just an example. You might want a more complex approach.)
char* generateFirstName(char* fileName) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        perror("Failed to open the name file");
        exit(EXIT_FAILURE);
    }

    char buffer[64];
    char* names[1000]; // Assuming there are a maximum of 100 names.
    int count = 0;

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        // Remove the trailing newline character if it exists
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        names[count] = strndup(buffer, len);
        count++;
    }
    fclose(f);

    if (count == 0) {
        fprintf(stderr, "No names found in the file\n");
        exit(EXIT_FAILURE);
    }

    char* selectedName = names[randomInRange(0, count - 1)];
    char* result = strndup(selectedName, strlen(selectedName));
    // Free memory allocated for names (but not the selected name)
    for (int i = 0; i < count; i++) {
        free(names[i]);
    }

    return result;
}


char* generateLastName(char* fileName) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        perror("Failed to open the name file");
        exit(EXIT_FAILURE);
    }

    char buffer[64];
    char* names[1000]; // Assuming there are a maximum of 100 names.
    int count = 0;

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        // Remove the trailing newline character if it exists
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        names[count] = strndup(buffer, len);
        count++;
    }
    fclose(f);

    if (count == 0) {
        fprintf(stderr, "No names found in the file\n");
        exit(EXIT_FAILURE);
    }

    char* selectedName = names[randomInRange(0, count - 1)];
    char* result = strndup(selectedName, strlen(selectedName));
    // Free memory allocated for names (but not the selected name)
    for (int i = 0; i < count; i++) {
        free(names[i]);
    }
    return result;
}


// Main generation function
void generateData(int cols[], int rowCount, char* fileName) {
    srand(time(NULL)); // Initialize random seed

    char buffer[264]; // 256 for name + 8 for ".csv" and null terminator
    snprintf(buffer, sizeof(buffer), "%s.csv", fileName);
    FILE* file = fopen(buffer, "wt");
    
    if (!file) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < rowCount; i++) {
        int colCount = 0;
        while (cols[colCount] != 0) colCount++;

        for (int j = 0; j < colCount; j++) {
            switch (cols[j]) {
                case 1:
                    fprintf(file, "%d", generateUserID());
                    break;
                case 2:
                    fprintf(file, "%s", generateFirstName("first_names.txt"));
                    break;
                case 3:
                    fprintf(file, "%s", generateLastName("last_names.txt"));
                    break;
                default:
                    break;
            }
            if (j < colCount - 1) {
                fprintf(file, ",");
            }
        }
    }

    fclose(file);
}