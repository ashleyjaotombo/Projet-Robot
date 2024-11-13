//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_STACK_H
#define UNTITLED1_STACK_H
#include "moves.h"

/**
 * @brief Structure for the stack of integers
 */
typedef struct s_stack
{
    t_move *values;
    int size;
    int nbElts;
}t_stack;

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(t_move);

/**
 * @brief Function to push a value in the stack
 * @param pointer to the stack
 * @param value : the value to push
 * @return none
 */
void push(t_stack *, t_move);

/**
 * @brief Function to pop a value from the stack
 * @param : pointer to the stack
 * @return the value popped
 */
t_move pop(t_stack *);

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
t_move top(t_stack);