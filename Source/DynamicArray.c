#include "DynamicArray.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void initDynamicArray(DynamicArray* arr, int elementSize, int capacity){
    arr->buffer = malloc(elementSize * capacity);
    if(arr->buffer == NULL){
        printf("Nao foi possivel alocar memoria: initDynamicArray\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = capacity;
    arr->elementSize = elementSize;
}

void destroyDynamicArray(DynamicArray* arr){
    free(arr->buffer);
}

void addToDynamicArray(DynamicArray* arr, void* element){
    if(arr->size >= arr->capacity){
        int cap = arr->capacity;
        arr->capacity = arr->capacity + arr->capacity / 2;
        void* temp = malloc(arr->capacity * arr->elementSize);
        memcpy(temp, arr->buffer, cap * arr->elementSize);
        free(arr->buffer);
        arr->buffer = temp;
    }
    memcpy((char*)arr->buffer + arr->size++ * arr->elementSize, element, arr->elementSize);
}

void getDynamicArray(DynamicArray* arr, int idx, void* element){
    if(idx >= arr->size){
        printf("Dynamic array overflow\n");
        exit(1);
    }
    memcpy(element, (char*)arr->buffer + idx * arr->elementSize, arr->elementSize);
}

void clearDynamicArray(DynamicArray* arr){
    arr->size = 0;
}

void copyDynamicArray(DynamicArray* dest, DynamicArray* source){
    if(dest->capacity < source->size || dest->elementSize != source->elementSize){
        printf("Cannot copy to buffer\n");
        exit(1);
    }
    memcpy(dest->buffer, source->buffer, source->size * source->elementSize);
    dest->elementSize = source->elementSize;
    dest->size = source->size;
}
