#ifndef __STACK_H__

#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct stack_entry_t
{
    void *data;
    struct stack_entry_t *next;
} stack_entry_t;

typedef struct stack
{
   stack_entry_t  *top;             /* Top of stack. */
} Stack_t;

void stack_init(Stack_t *stack)
{
    stack->top  = NULL;
}

int stack_empty(Stack_t *stack)
{
    return (!stack->top);
}

void *stack_top(Stack_t *stack)
{
    return stack->top;
}

/*
 * Add new entry into the stack.
 * Returns 0 on success -1 on failure.
 *
 * @stack : Pointer to the stack.
 * @entry : New entry that needs to be added into the stack.
 */ 
int stack_push(Stack_t *stack, void *entry)
{
    assert(stack);

    stack_entry_t *new_entry = (stack_entry_t *) malloc(sizeof (stack_entry_t));

    if (!new_entry)
    {
        LOG_ERR("Failed to allocate memory for the new entry.");
        return -1;
    }

    new_entry->data = entry;
    new_entry->next = NULL;

    new_entry->next = stack->top;
    stack->top = new_entry;

    return 0;
}

/*
 * Remove entry at the top of the stack and return its data part.
 *
 * @stack : Pointer to the stack.
 */
void *stack_pop(Stack_t *stack)
{
    assert(stack);

    if (stack_empty(stack))
    {
        return NULL;
    }

    stack_entry_t *entry = stack->top;
    assert(entry);
    void *data = entry->data;

    stack->top = stack->top->next;
    free(entry);

    return data;
}

/*
 * Print all entries in the stack from top to bottom of the stack.
 * ASSUMPTION: All entries have int as their data part.
 */
void stack_print(Stack_t *stack)
{
    assert(stack);

    stack_entry_t *entry = stack->top;

    while (entry)
    {
        printf("%d ", *(int *) entry->data);
        entry = entry->next;
    }
}

void stack_destroy(Stack_t *stack)
{
    assert(stack);

    while (!stack_empty(stack))
    {
        stack_pop(stack);
    }
}

/*
 * Create stack for given number of entries and for each entry accept data from stdin.
 * Return pointer to the stack on success and NULL on failure.
 *
 * @n : Number of entries.
 */
Stack_t *stack_create(unsigned int n)
{
    Stack_t *stack = (Stack_t *) malloc(sizeof (Stack_t));
    unsigned int i = 0;

    if (!stack)
    {
        LOG_ERR("Failed to allocate memory for stack.");
        return NULL;
    }

    stack_init(stack);

    for (i = 0; i < n; i++)
    {
        int *entry = (int *) malloc(sizeof (int));

        if (!entry)
        {
            LOG_ERR("Failed to allocate memory for stack entry.");
            goto err;
        }

        scanf("%d", entry);

        if (stack_push(stack, entry) != 0)
        {
            goto err;
        }
    }

    return stack;

err:
    while (!stack_empty(stack))
    {
        free(stack_pop(stack));
    }

    free(stack);

    return NULL;
}

#endif //__STACK_H__
