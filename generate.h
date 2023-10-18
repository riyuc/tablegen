#ifndef GENERATE_H
#define GENERATE_H

typedef struct {
    int userID;
    char firstName[64];
    char lastName[64];
    char phoneNumber[12];
    char country[64];
    char email[64];
    int sin;
    char password[16];
} Person;

void generateData(int cols[], int choiceRow, char* choiceName);
int rngrand(int min, int max);
int generateNumber(int min, int max);
char* generatePhoneNumber();
char* generateFromFile(char* fileName,int rowCount);
char* generateEmail(char* firstName, char* lastName);
char* generatePassword();
Person generatePerson();

#endif // GENERATE_H
