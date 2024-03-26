#include <stdio.h>
#include "stamp.h"

int main(void) {
    struct Stamp stamps[100];
    int stampCount = 0;

    // Считываем данные о марках из файлов
    if (!readStampsFromFile("additional_info.txt", stamps, &stampCount)) {
        printf("Ошибка при чтении марок из файла in.txt.\n");
        return 1;
    }

    // Считываем дополнительные данные о марках из файла stamps_details.txt
    if (!readStampsDetailsFromFile("stamps_details.txt", stamps, &stampCount)) {
        printf("Ошибка при чтении дополнительных данных о марках из файла stamps_details.txt.\n");
        return 1;
    }

    // Отображаем меню для работы с марками
    displayMenu(stamps, &stampCount);

    // Записываем отсортированные марки в файл
    if (!writeSortedStampsToFile("out.txt", stamps, stampCount)) {
        printf("Ошибка при записи марок в файл out.txt.\n");
        return 1;
    }

    return 0;
}
