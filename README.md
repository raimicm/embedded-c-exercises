# embedded-c-exercises

This repository contains self-directed C programming exercises exploring embedded systems design patterns. The goal of these exercises is to practice writing C code using techniques commonly used in embedded applications, independent of specific hardware.

## State Machine

In the `state_machine/` directory, the following state machine with 4 states is implemented:

<div align="center">
    <img src="./state_machine/state_machine.png" width="40%" alt="State Machine" style="display: block; margin: 5 auto;">
</div>

where $i$ is the user input value to trigger each state switch shown by the arrows.

Each state has its own handler function that returns the next state given the user input. Each handler is collected into a single function array to act as a dispatcher:

```C
sm_state (*state_handlers[])(int input) = {
    state_A_handler,
    state_B_handler,
    state_C_handler,
    state_D_handler
};
```

This dispatcher chooses the handler function corresponding the current state, allowing for simple state switch logic:

```C
sm_state next_state(sm_state state, int input) {
    return state_handlers[state](input);
}
```

This design avoids large switch statements, improving
**maintainability** and **scalability**.

## Interface Abstraction

The `interface/` directory demonstrates the use of an interface using a structure of function pointers. In this example, there are two buffers with different implementations:

```C
int buffer1[BUFFER_SIZE];
int* buffer2[BUFFER_SIZE];
```

`buffer1` is simply an array of integers, whereas `buffer2` is an array of pointers to integers, so the processes of reading and writing data (integers) is different for each:

```C
int buffer1_read(int idx) {
    return buffer1[idx];
}

void buffer1_write(int idx, int val) {
    buffer1[idx] = val;
}

int buffer2_read(int idx) {
    return *(buffer2[idx]);
}

void buffer2_write(int idx, int val) {
    *(buffer2[idx]) = val;
}
```

Despite these differences in implementation, `buffer1_read()` and `buffer2_read()` serve the same purpose. This is where interfaces come into play. The type `buffer_operations` is introduced to define the necessary operations on a buffer:

```C
typedef struct {
    int (*read)(int idx);
    void (*write)(int idx, int val);
} buffer_operations;
```

Now, the `buffer_operations` for `buffer1` and `buffer2` can be put into an array:

```C
buffer_operations buf_ops[2] = {
    {buffer1_read, buffer1_write},
    {buffer2_read, buffer2_write},
}
```

This adds a layer of abstraction, allowing the user to perform an operation on a buffer without having to worry about the specifics of the implementation and calling the correct read/write function:

```C
buf_ops[0].read(i); // buffer 1
buf_ops[1].read(i); // buffer 2

buf_ops[0].write(i, 0); // buffer 1
buf_ops[1].write(i, 0); // buffer 2
```

This design encourages:
- **Portability:** Separates high-level operations from implementation, enabling reuse across different hardware.
- **Scalability:** More implementations can be introduced without altering existing code.
- **Maintainability:** Implementation changes are isolated.