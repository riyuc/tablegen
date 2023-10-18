#include "sort.h"
#include "generate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int comparePersons(const void *a, const void *b) {
    Person *personA = (Person *)a;
    Person *personB = (Person *)b;

    char *lastNameA = personA->lastName;
    char *lastNameB = personB->lastName;

    while (*lastNameA && *lastNameB) {
        if (*lastNameA != *lastNameB) {
            return *lastNameA - *lastNameB;
        }
        // Move on to the next characters
        lastNameA++;
        lastNameB++;
    }

    // If one last name is a prefix of the other, return the difference in lengths
    return *lastNameA - *lastNameB;
}

void sortPersonsByLastName(Person persons[], int count) {
    qsort(persons, count, sizeof(Person), comparePersons);
}