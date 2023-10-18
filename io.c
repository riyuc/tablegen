#include "io.h"
#include "generate.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "constants.h"

const char* generateColumnHeader(int colNumber) {
    
    switch (colNumber) {
        case 1: 
            return "User ID";
        case 2: 
            return "First Name";
        case 3: 
            return "Last Name";
        case 4: 
            return "Country";
        case 5: 
            return "Phone";
        case 6: 
            return "Email";
        case 7: 
            return "SIN";
        case 8: 
            return "Password";
        default: 
            return "";
    }
}

void generateData(int cols[], int rowCount, char* fileName){
    srand(time(NULL));

    Person persons[rowCount];
    for (int i = 0; i < rowCount; i++) {
        persons[i] = generatePerson();
        persons[i].userID = i + 1;
    }
    sortPersonsByLastName(persons,rowCount);
    char buffer[264];
    snprintf(buffer, sizeof(buffer), "%s.csv", fileName);
    FILE* file = fopen(buffer, "wt");

    int colCount = 0;
    while (cols[colCount] != 0) colCount++;

    for (int j = 0; j < colCount; j++) {
        fprintf(file, "%s", generateColumnHeader(cols[j]));
        if (j < colCount - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");
    
    for (int i = 0; i < rowCount; i++) {
        Person person = persons[i];
        int colCount = 0;
        while (cols[colCount] != 0) colCount++;

        for (int j = 0; j < colCount; j++) {
            switch (cols[j]) {
                case 1:
                    fprintf(file, "%d", person.userID);
                    break;
                case 2:
                    fprintf(file, "%s", person.firstName);
                    break;
                case 3:
                    fprintf(file, "%s", person.lastName);
                    break;
                case 4:
                    fprintf(file, "%s", person.country);
                    break;
                case 5:
                    fprintf(file, "%s", person.phoneNumber);
                    break;
                case 6:
                    fprintf(file, "%s", person.email);
                    break;
                case 7:
                    fprintf(file, "%d", person.sin);
                    break;
                case 8:
                    fprintf(file, "%s", person.password);
                    break;
                default:
                    break;
            }
            if (j < colCount - 1){
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
