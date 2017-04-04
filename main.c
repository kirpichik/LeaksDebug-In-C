//
//  main.c
//  LeaksDebug
//
//  Created by Кирилл on 04.04.17.
//  Copyright © 2017 Кирилл. All rights reserved.
//

#include <stdio.h>

/** В каждом файле, в котором мы хотим отследить выделение и освобождение памяти, 
 * нужно заменить #include <stdlib.h> на #include "leaks_debug.h". Файл leaks_debug.h
 * уже имеет в себе stdlib.h. */
#include "leaks_debug.h"

#define ARRAY_MEMORY_LEAKS_SIZE 10

/** Пример с утечками памяти. */
void memoryLeaksExample() {

    // Создадим массив и заполним указателями на числа
    int* nums[ARRAY_MEMORY_LEAKS_SIZE];
    
    printf("Creating the array[%d] on heap...\n", ARRAY_MEMORY_LEAKS_SIZE);
    for (int i = 0; i < ARRAY_MEMORY_LEAKS_SIZE; i++) {
        nums[i] = (int*) malloc(sizeof(int));
        (*nums[i]) = ARRAY_MEMORY_LEAKS_SIZE - i;
    }
    
    // Распечатаем массив
    printf("Printint the array...\n");
    for (int i = 0; i < ARRAY_MEMORY_LEAKS_SIZE; i++)
        printf("%d ", (*nums[i]));
    
    printf("\n");
    
    // Выведем все объекты, которые на данный момент выделены и не освобождены.
    // Так как память за указателями в массиве мы не очищали, в выводе должно оказаться 10 объектов.
    _dumpMemoryLeaks();
    
    printf("Oh God, the memory ran away!\n");
}

/** Пример без утечек памяти. */
void noMemoryLeaksExample() {

    // Создадим массив и заполним указателями на числа
    int* nums[ARRAY_MEMORY_LEAKS_SIZE];
    
    printf("Creating the array[%d] on heap...\n", ARRAY_MEMORY_LEAKS_SIZE);
    for (int i = 0; i < ARRAY_MEMORY_LEAKS_SIZE; i++) {
        nums[i] = (int*) malloc(sizeof(int));
        (*nums[i]) = ARRAY_MEMORY_LEAKS_SIZE - i;
    }
    
    // Распечатаем массив
    printf("Printing the array...\n");
    for (int i = 0; i < ARRAY_MEMORY_LEAKS_SIZE; i++)
        printf("%d ", (*nums[i]));
    
    printf("\n");
    
    // Освободим все указатели, которые мы выделили ранее
    printf("Releasing the array...\n");
    for (int i = 0; i < ARRAY_MEMORY_LEAKS_SIZE; i++)
        free(nums[i]);
    
    // Выведем все объекты, которые на данный момент выделены и не освобождены.
    // Так как мы выделили указатели, а потом очистили их, в выводе не должно оказаться никаких объектов.
    _dumpMemoryLeaks();
    
    printf("We have no leaks!\n");
}

int main(int argc, const char * argv[]) {
    
    // Пример вывода без утечек памяти
    printf("No memory leaks example start:\n");
    noMemoryLeaksExample();
    printf("No memory leaks example end.\n\n");
    
    // Пример вывода с утечками памяти
    printf("Memory leaks example start:\n");
    memoryLeaksExample();
    printf("Memory leaks example end.\n\n");
    
    // В конце програмы нужно очистить список запомненных не освобожденных объектов
    printf("Releasing leaks debug...\n");
    _freeHeapList();
    
    return 0;
}
