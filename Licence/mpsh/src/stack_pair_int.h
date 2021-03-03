#ifndef STACK_PAIR_INT_H
#define STACK_PAIR_INT_H

#define STACK_SIZE 32

/**
 * @brief Pair of int.
 */
typedef struct pair_int
{
  int x;
  int y;
} pair_int_t;

/**
 * @brief stack of pair_int_t
 */
typedef struct stack_pair_int
{
  /*! Array of elements !*/
  pair_int_t **array;
  /*! Number of elements in the stack !*/
  int size;
  /*! Current max size of the array !*/
  int current_max;
} stack_pair_int_t;

pair_int_t *gen_pair_int(int x, int y);

/**
 * @brief Initializes a new stack_pair_int_t.
 * 
 * @return stack_pair_int_t Generated stack_pair_int_t.
 */
stack_pair_int_t *gen_stack_pair_int();

/**
 * @brief Gets the element on top of the stack.
 * 
 * @param stack Stack to get an element from.
 * @param addr Address to write the element to.
 * @return int 1 if success else 0.
 */
int stack_pair_int_get(stack_pair_int_t *stack, pair_int_t **addr);

/**
 * @brief Gets the element on top of the stack and removes it from the stack.
 * 
 * stack Stack to use.
 * @param addr Address to write the element to.
 * @return int 1 if success else 0.
 */
int stack_pair_int_pop(stack_pair_int_t *stack, pair_int_t **addr);

/**
 * @brief Adds an element on top of the stack.
 * 
 * stack Stack to use.
 * @param pair Pair to add.
 * @return int 1 if success else 0.
 */
int stack_pair_int_add(stack_pair_int_t *stack, pair_int_t *pair);

/**
 * @brief Expands the array of the stack.
 * 
 * Doubles the array size.
 * 
 * @param stack stack to expand the 
 * @return int 1 if success else 0.
 */
int stack_pair_int_expand_array(stack_pair_int_t *stack);

/**
 * @brief Test for this struct.
 * 
 * @return int 1 if success else 0.
 */
int stack_pair_int_test();

#endif // STACK_PAIR_INT_H
