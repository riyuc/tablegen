#include "generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "io.h"
#include "constants.h"

int rngrand(int min, int max) {
    return min + rand() % (max - min + 1);
}

int generateUserID() {
    static int id = 1;
    return id++; // Example range
}

char* generatePhoneNumber() {
    int prefix[] = {398, 270, 925, 867, 209, 429, 908, 997, 444, 219};
    int numIndices = sizeof(prefix) / sizeof(prefix[0]);
    int suffix = rngrand(1000, 9999); 

    char* phoneNumber = malloc(9 * sizeof(char)); 
    snprintf(phoneNumber, 9, "%d-%d", prefix[rngrand(0, numIndices - 1)], suffix);

    return phoneNumber;
}

char* generateFromFile(char* fileName,int rowCount) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        perror("Failed to open the name file");
        exit(EXIT_FAILURE);
    }

    char buffer[64];
    // char** names = malloc((rowCount+1) * sizeof(char*));
    char* names[1000];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
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

    char* selectedName = names[rngrand(0, count - 1)];
    char* result = strndup(selectedName, strlen(selectedName));
    for (int i = 0; i < count; i++) {
        if (names[i] != NULL) {
            free(names[i]);
        }
    }
    return result;
}

char* generateEmail(char* firstName, char* lastName) {
    char* suffix = generateFromFile("email_suffixes.txt", userRowCount);
    
    size_t emailSize = strlen(firstName) + strlen(lastName) + strlen(suffix) + 3; // +3 for the '@', initial of the first name, and null terminator.
    char* email = (char*)malloc(emailSize * sizeof(char));
    
    snprintf(email, emailSize, "%c%s@%s", firstName[0], lastName, suffix);

    // Convert entire email to lowercase
    for (int i = 0; email[i]; i++) {
        email[i] = tolower(email[i]);
    }

    free(suffix); // Don't forget to free the suffix memory after use

    return email;
}

char* generatePassword() {
    int length = rngrand(6, 16);
    char* password = malloc((length + 1) * sizeof(char));

    for (int i = 0; i < length; i++) {
        char ch;
        do {
            ch = rngrand(33,126);
        } while(ch == 44);

        password[i] = ch;
    }
    password[length] = '\0';
    return password;
}


Person generatePerson(){
    Person p;
    
    p.sin = rngrand(100000000,999999999);
    char* firstName = generateFromFile("first_names.txt",userRowCount);
    char* lastName = generateFromFile("last_names.txt",userRowCount);
    char* country = generateFromFile("countries.txt",userRowCount);
    char* phoneNumber = generatePhoneNumber();
    char* email = generateEmail(firstName, lastName);
    char* password = generatePassword();

    strcpy(p.firstName, firstName);
    strcpy(p.lastName, lastName);
    strcpy(p.country, country);
    strcpy(p.phoneNumber, phoneNumber);
    strcpy(p.email, email);
    strcpy(p.password, password);

    free(firstName);
    free(lastName);
    free(country);
    free(phoneNumber);
    free(email);
    free(password);

    return p;
}
