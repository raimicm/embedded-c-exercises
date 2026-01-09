#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 10

int buffer1[BUFFER_SIZE];
int* buffer2[BUFFER_SIZE];

typedef enum {
    BUFFER1 = 0,
    BUFFER2
} buffer_id;

// buffer interface
typedef struct {
    int (*read)(int idx);
    void (*write)(int idx, int val);
} buffer_operations;

// buffer1 operations
int buffer1_read(int idx) {
    return buffer1[idx];
}

void buffer1_write(int idx, int val) {
    buffer1[idx] = val;
}

// buffer2 operations
int buffer2_read(int idx) {
    return *(buffer2[idx]);
}

void buffer2_write(int idx, int val) {
    *(buffer2[idx]) = val;
}

// sets up buffer2
int buffer2_init() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        int *p = (int*) malloc(sizeof(int));
        if (p == NULL)
            return -1;

        *p = 0;
        buffer2[i] = p;
    }
    return 0;
}

// cleans up buffer2
void buffer2_free() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        free(buffer2[i]);
    }
}

// dispatcher
buffer_operations buf_ops[2] = {
    {buffer1_read, buffer1_write},
    {buffer2_read, buffer2_write},
};

int main() {
    if (buffer2_init()) {
        printf("Failed to allocate memory for buffer2.\n");
        return 1;
    }

    printf("Initial values:\n");
    printf("idx   buffer1   buffer2\n");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        int val1 = buf_ops[BUFFER1].read(i);
        int val2 = buf_ops[BUFFER2].read(i);

        printf("%3d   %7d   %7d\n", i, val1, val2);
    }

    for (int i = 0; i < BUFFER_SIZE; i++) {
        buf_ops[BUFFER1].write(i, 2*i);
        buf_ops[BUFFER2].write(i, 2*i);
    }

    printf("\nAfter writes:\n");
    printf("idx   buffer1   buffer2\n");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        int val1 = buf_ops[BUFFER1].read(i);
        int val2 = buf_ops[BUFFER2].read(i);

        printf("%3d   %7d   %7d\n", i, val1, val2);
    }

    buffer2_free();
    return 0;
}