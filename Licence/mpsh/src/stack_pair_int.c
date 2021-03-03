#include "stack_pair_int.h"
#include <stdlib.h>

pair_int_t *gen_pair_int(int x, int y) {
  pair_int_t *pair = malloc(sizeof(pair_int_t));
  pair->x = x;
  pair->y = y;
  return pair;
}

stack_pair_int_t *gen_stack_pair_int() {
  stack_pair_int_t *stack = malloc(sizeof(stack_pair_int_t));
  stack->array = malloc(sizeof(pair_int_t *) * STACK_SIZE);
  stack->size = 0;
  stack->current_max = STACK_SIZE;
  return stack;
}

int stack_pair_int_get(stack_pair_int_t *stack, pair_int_t **addr) {
  if (stack->size == 0) {
    *addr = NULL;
    return 0;
  }
  *addr = stack->array[stack->size - 1];
  return 1;
}

int stack_pair_int_pop(stack_pair_int_t *stack, pair_int_t **addr) {
  if (!stack_pair_int_get(stack, addr))
    return 0;
  stack->size--;
  return 1;
}

int stack_pair_int_add(stack_pair_int_t *stack, pair_int_t *pair) {
  if (stack->size >= stack->current_max)
    if (!stack_pair_int_expand_array(stack))
      return 0;
  stack->array[stack->size] = pair;
  stack->size++;
  return 1;
}

int stack_pair_int_expand_array(stack_pair_int_t *stack) {
  stack->array =
      realloc(stack->array, sizeof(pair_int_t *) * stack->current_max * 2);
  if (!stack->array)
    return 0;
  return 1;
}

int stack_pair_int_test() {
  stack_pair_int_t * stack = gen_stack_pair_int();
  stack_pair_int_add(stack, gen_pair_int(1, 6));
  stack_pair_int_add(stack, gen_pair_int(2, 6));
  stack_pair_int_add(stack, gen_pair_int(3, 6));
  return 0;
}
