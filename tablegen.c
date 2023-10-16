#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "io.h"
#include "generate.h"
#include "sort.h"
#include "constants.h"

int main(){
    system("clear");
    srand(time(NULL));
    int choiceMain;
    char choiceColumn[16];
    int choiceRow;
    char* choiceName = NULL;
    printf("TableGen Menu\n");
    printf("----------------\n");
    printf("1. Generate new table\n");
    printf("2. Exit\n\n");
    printf("Selection: ");
    scanf("%i", &choiceMain);
    switch (choiceMain)
    {
    case 1:
        system("clear");
        printf("Column Options\n");
        printf("---------------\n");
        printf("1. User ID \t 5. Phone Number\n");
        printf("2. First Name \t 6. Email Address\n");
        printf("3. Last Name \t 7. SIN\n");
        printf("4. Country \t 8. Password\n\n");
        printf("Enter column list (comma-separated, no spaces): ");
        scanf("%s", choiceColumn);

        int cols[MAX_COLS];
        char *split = strtok(choiceColumn, ",");
        int i = 0;
        while(split != NULL) {
            cols[i++] = atoi(split);
            split = strtok(NULL, ",");
        }
        // Print parsed columns
        for(int i = 0; i < MAX_COLS; i++){
            if(cols[i] > 0) {
                printf("%d ", cols[i]); 
            }
        }

        printf("\nEnter row count (1 < n < 1M): ");
        scanf("%i", &choiceRow);
        printf("\nEnter output file name (no suffix): ");
        choiceName = (char*) malloc(64 * sizeof(char)); 
        scanf("%s", choiceName);
        printf("\nSummary of Properties:");
        printf("\nColumns: %s", choiceColumn);
        printf("\nRow count: %i", choiceRow);
        printf("\nFile name: %s", choiceName);
        printf("\nTable written successfully to %s.csv", choiceName);
        generateData(cols, choiceRow, choiceName);

        free(choiceName);
        printf("\nPress 'c' or 'C' to contine\n");
        break;
    case 2:
        printf("Thank you for using TableGen\n");
        exit(0);
    default:
        break;
    }

    return 0;
}