#include <stdio.h>
#include "stamp.h"

int main(void) {
    struct Stamp stamps[100];
    int stampCount = 0;

    if (!readStampsFromFile("in.txt", stamps, &stampCount)) {
        printf("Ошибка при чтении марок из файла.\n");
        return 1;
    }

    displayMenu(stamps, &stampCount);

    if (!writeSortedStampsToFile("out.txt", stamps, stampCount)) {
        printf("Ошибка при записи марок в файл.\n");
        return 1;
    }

    return 0;
}
