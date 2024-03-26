//добавлена вторая функция для считывания второго файла. заняло 15 минут вместе с прописыванием логики работы функции в stamp.c
#include <stdio.h>
#include "stamp.h"

int main(void) {
    struct Stamp stamps[100];
    int stampCount = 0;

    if (!readStampsFromFile("in1.txt", stamps, &stampCount)) {
        printf("Ошибка при чтении марок из файла in.txt.\n");
        return 1;
    }

    if (!readStampsDetailsFromFile("in2.txt", stamps, &stampCount)) {
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
