#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Possible states
typedef enum {
    state_A = 0,
    state_B,
    state_C,
    state_D
} sm_state;

char state_chars[] = {'A', 'B', 'C', 'D'};

// Handlers for each state

sm_state state_A_handler(int input) {
    if (0 == input)
        return state_B;
    else if (1 == input)
        return state_C;
    else
        return state_A;
}

sm_state state_B_handler(int input) {
    if (2 == input)
        return state_D;
    if (4 == input)
        return state_C;
    else
        return state_B;
}

sm_state state_C_handler(int input) {
    if (3 == input)
        return state_D;
    else
        return state_C;
}

sm_state state_D_handler(int input) {
    if (5 == input)
        return state_A;
    else
        return state_D;
}

// Function array containing all handlers
sm_state (*state_handlers[])(int input) = {
    state_A_handler,
    state_B_handler,
    state_C_handler,
    state_D_handler
};

// Helper function to compute next state
sm_state next_state(sm_state state, int input) {
    return state_handlers[state](input);
}

int main() {
    sm_state current_state = state_A;

    for (;;) {
        printf("Current state: %c - Input integer: ", state_chars[current_state]);

        int input;
        scanf("%d", &input); // user inputs an integer

        if (input < 0)
            break; // enter negative value to exit

        current_state = next_state(current_state, input);
    }
    
    return 0;
}

