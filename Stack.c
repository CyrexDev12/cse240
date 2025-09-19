#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int *stack = NULL;
int top_index = -1;
int capacity = 0;

/*
Stack Representation:

Initially:
Capacity = 2
  +---+---+
  |   |   |
  +---+---+
   0   1

After pushing 10:
Capacity = 2
  +----+---+
  | 10 |   |
  +----+---+
   0    1

After pushing 20:
Capacity = 2
  +----+----+
  | 10 | 20 |
  +----+----+
   0    1

After pushing 30 (resize):
Capacity = 4
  +----+----+----+----+
  | 10 | 20 | 30 |    |
  +----+----+----+----+
   0    1    2    3

After popping (30 is removed):
Capacity = 4
  +----+----+----+----+
  | 10 | 20 |    |    |
  +----+----+----+----+
   0    1    2    3
*/

// Function to initialize the stack
void initialize_stack(int initialCapacity) {
    /** CODE: initialize memory for stack onto the HEAP 
     *        set the capacity to initalCapacity  
     */
    capacity = initialCapacity;
    stack = malloc((size_t)capacity * sizeof(stack));
}

// Function to resize the stack
void resize_stack() {
    /** CODE: increase size of heap based array by doubling it
     */
    capacity *= 2; 
    int *tmp = realloc(stack, 2 * sizeof(stack));
    stack = tmp; 
}

// Function to push an element onto the stack
void push(int value) {
    /** CODE: if the top is equal to capacity -1 then resizeStack 
     *        increase top
     *        add value to stack
    */
   if (top_index == capacity - 1) {
        resize_stack();
   }

    top_index++; 
    stack[top_index] = value;
}

// Function to pop an element from the stack
int pop() {
    /** CODE: check if any values are on stack, if not, return -1 
     *        else, return the current top item and decrement the top_index */
    if (top_index == -1) {
    return -1;
    } 

    int val = stack[top_index];
    top_index--;

    return val; 

}

// Function to peek at the top element of the stack
int top() {
    /** CODE: check if any values are on stack, if not, return -1 
     *        else, return the current top item  */
    if (top_index == -1) {
    return -1;
    } 

    return stack[top_index];
}

// Function to check if the stack is empty
int isEmpty() {
    /** CODE: return true if no items are left on the stack else return false
     *        This can be done with returning a single conditional statement */

    return top_index == -1; 
}

// Function to free the stack
void freeStack() {
    free(stack);
}
