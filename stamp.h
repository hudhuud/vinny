#ifndef STAMP_H
#define STAMP_H

#define MAX_STAMPS 100
#define MAX_NAME_LENGTH 50
#define MAX_COUNTRY_LENGTH 50

struct Stamp {
    int index;
    char name[MAX_NAME_LENGTH];
    char country[MAX_COUNTRY_LENGTH];
    int year;
    int albumNumber;
    int price;
};

int readStampsFromFile(const char *fileName, struct Stamp stamps[], int *stampCount);

int writeSortedStampsToFile(const char *fileName, struct Stamp stamps[], int stampCount);

int readStampsDetailsFromFile(const char *fileName, struct Stamp stamps[], int *stampCount);

void displayMenu(struct Stamp stamps[], int *stampCount);

void addStampMenu(struct Stamp stamps[], int *stampCount);

void deleteStampMenu(struct Stamp stamps[], int *stampCount);

void editStampMenu(struct Stamp stamps[], int *stampCount);

void printAllStampsMenu(struct Stamp stamps[], int *stampCount);

void query1Menu(struct Stamp stamps[], int *stampCount);

void query2Menu(struct Stamp stamps[], int *stampCount);

void exitMenu(struct Stamp stamps[], int *stampCount);

#endif
