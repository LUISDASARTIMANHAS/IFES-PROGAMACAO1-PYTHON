#include <stdlib.h>
#include <stdio.h>
#include "functions.c"
#define TAM 10

int main(){
    head();
    int data3[TAM] = {3794, 4730, 4026, 993, 1349, 917, 3224, 7634, 9898, 6724};
    int data2[TAM] = {41, 90, 4, 38, 67, 19, 57, 54, 44, 50};
    int data[TAM] = {10, 20, 30,40, 50, 60, 70, 80, 90, 100};

    insertionSort(data2,TAM);

    copy();
    return 0;
}