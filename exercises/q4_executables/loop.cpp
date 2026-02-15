#include <stdio.h> 

#define ARRAY_SIZE  5

int main() {

    short array[ARRAY_SIZE] = {};

    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i;
    }

    printf("%d\n", array[2]);

    return 0;
}
