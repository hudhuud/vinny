#include "stamp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIndices(const void *a, const void *b) {
    return ((struct Stamp *)a)->index - ((struct Stamp *)b)->index;
}

int readStampsFromFile(const char *fileName, struct Stamp stamps[], int *stampCount) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Ошибка при открытии файла: %s\n", fileName);
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%d %s %s %d %d %d", &stamps[count].index, stamps[count].name, stamps[count].country,
                  &stamps[count].year, &stamps[count].albumNumber, &stamps[count].price) != EOF) {
        count++;
    }

    *stampCount = count;
    fclose(file);
    return 1;
}

int writeSortedStampsToFile(const char *fileName, struct Stamp stamps[], int stampCount) {
    FILE *file = fopen(fileName, "w");
    if (!file) {
        printf("Ошибка при открытии файла: %s\n", fileName);
        return 0;
    }

    qsort(stamps, stampCount, sizeof(struct Stamp), compareIndices);

    fprintf(file, "Индекс Название Страна Год НомерАльбома Цена\n");
    for (int i = 0; i < stampCount; i++) {
        fprintf(file, "%d %s %s %d %d %d\n", stamps[i].index, stamps[i].name, stamps[i].country,
                stamps[i].year, stamps[i].albumNumber, stamps[i].price);
    }

    fclose(file);
    return 1;
}
int countStampsByYear(struct Stamp stamps[], int stampCount, int year) {
    int count = 0;
    for (int i = 0; i < stampCount; i++) {
        if (stamps[i].year == year) {
            count++;
        }
    }
    return count;
}

int totalCostOfStampsByYear(struct Stamp stamps[], int stampCount, int year) {
    int totalCost = 0;
    for (int i = 0; i < stampCount; i++) {
        if (stamps[i].year == year) {
            totalCost += stamps[i].price;
        }
    }
    return totalCost;
}
void displayMenu(struct Stamp stamps[], int *stampCount);

void addStampMenu(struct Stamp stamps[], int *stampCount) {
    if (*stampCount >= 30) {
        printf("Невозможно добавить больше марок. Достигнуто максимальное количество.\n");
        return;
    }

    struct Stamp newStamp;
    printf("Введите индекс новой марки: ");
    scanf("%d", &newStamp.index);
    printf("Введите название марки: ");
    scanf("%s", newStamp.name);
    printf("Введите страну: ");
    scanf("%s", newStamp.country);
    printf("Введите год выпуска: ");
    scanf("%d", &newStamp.year);
    printf("Введите номер альбома: ");
    scanf("%d", &newStamp.albumNumber);
    printf("Введите цену: ");
    scanf("%d", &newStamp.price);

    stamps[*stampCount] = newStamp;
    (*stampCount)++;
    printf("Марка успешно добавлена.\n");
}

void deleteStampMenu(struct Stamp stamps[], int *stampCount) {
    int indexToDelete;
    printf("Введите индекс марки для удаления: ");
    scanf("%d", &indexToDelete);
    
    int found = 0;
    for (int i = 0; i < *stampCount; i++) {
        if (stamps[i].index == indexToDelete) {
            found = 1;
            // Перемещение последнего элемента на место удаляемого элемента
            stamps[i] = stamps[*stampCount - 1];
            (*stampCount)--;
            printf("Марка с индексом %d успешно удалена.\n", indexToDelete);
            break;
        }
    }

    if (!found) {
        printf("Марка с индексом %d не найдена.\n", indexToDelete);
    }
}

void editStampMenu(struct Stamp stamps[], int *stampCount) {
    int indexToEdit;
    printf("Введите индекс марки для редактирования: ");
    scanf("%d", &indexToEdit);
    
    int found = 0;
    for (int i = 0; i < *stampCount; i++) {
        if (stamps[i].index == indexToEdit) {
            found = 1;
            printf("Текущая информация о марке с индексом %d:\n", indexToEdit);
            printf("Название: %s\n", stamps[i].name);
            printf("Страна: %s\n", stamps[i].country);
            printf("Год выпуска: %d\n", stamps[i].year);
            printf("Номер альбома: %d\n", stamps[i].albumNumber);
            printf("Цена: %d\n", stamps[i].price);

            printf("Введите новые данные:\n");
            printf("Введите новое название: ");
                        scanf("%s", stamps[i].name);
            printf("Введите новую страну: ");
            scanf("%s", stamps[i].country);
            printf("Введите новый год выпуска: ");
            scanf("%d", &stamps[i].year);
            printf("Введите новый номер альбома: ");
            scanf("%d", &stamps[i].albumNumber);
            printf("Введите новую цену: ");
            scanf("%d", &stamps[i].price);

            printf("Марка с индексом %d успешно отредактирована.\n", indexToEdit);
            break;
        }
    }

    if (!found) {
        printf("Марка с индексом %d не найдена.\n", indexToEdit);
    }
}

void printAllStampsMenu(struct Stamp stamps[], int *stampCount) {
    printf("Все марки:\n");
    for (int i = 0; i < *stampCount; i++) {
        printf("Индекс: %d\n", stamps[i].index);
        printf("Название: %s\n", stamps[i].name);
        printf("Страна: %s\n", stamps[i].country);
        printf("Год выпуска: %d\n", stamps[i].year);
        printf("Номер альбома: %d\n", stamps[i].albumNumber);
        printf("Цена: %d\n", stamps[i].price);
        printf("\n");
    }
}

void query1Menu(struct Stamp stamps[], int *stampCount) {
    int year;
    printf("Введите год: ");
    scanf("%d", &year);
    int count = countStampsByYear(stamps, *stampCount, year);
    printf("Количество марок, выпущенных в %d году: %d\n", year, count);
}

void query2Menu(struct Stamp stamps[], int *stampCount) {
    int year;
    printf("Введите год: ");
    scanf("%d", &year);
    int totalCost = totalCostOfStampsByYear(stamps, *stampCount, year);
    printf("Общая стоимость марок, выпущенных в %d году: %d\n", year, totalCost);
}

void exitMenu(struct Stamp stamps[], int *stampCount) {
    
}

typedef void (*MenuFunction)(struct Stamp stamps[], int *stampCount);

void displayMenu(struct Stamp stamps[], int *stampCount) {
    MenuFunction menuFunctions[] = {
        addStampMenu,
        deleteStampMenu,
        editStampMenu,
        printAllStampsMenu,
        query1Menu,
        query2Menu,
        exitMenu
    };

    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Добавить марку\n");
        printf("2. Удалить марку\n");
        printf("3. Редактировать марку\n");
        printf("4. Вывести все марки\n");
        printf("5. Подсчитать количество марок по году выпуска\n");
        printf("6. Подсчитать общую стоимость марок по году выпуска\n");
        printf("7. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        
        // Очистка буфера ввода
        while (getchar() != '\n');

        if (choice >= 1 && choice <= 7) {
            if (menuFunctions[choice - 1]) {
                menuFunctions[choice - 1](stamps, stampCount);
            } else {
                printf("Функция для выбранного пункта меню не реализована.\n");
            }
        } else {
            printf("Некорректный выбор. Пожалуйста, выберите число от 1 до 7.\n");
        }
    } while (choice != 7);
}

