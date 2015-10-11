#ifndef __QUEUE_H__

#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct queue_entry_t
{
    void *data;
    struct queue_entry_t *next;
} queue_entry_t;

typedef struct queue
{
   queue_entry_t  *front, *rear;
} queue_t;

void queue_init(queue_t *q)
{
    q->front = q->rear = NULL;
}

int queue_empty(queue_t *q)
{
    return (!q->front);
}

/*
 * Add new entry into the queue.
 * Returns 0 on success -1 on failure.
 *
 * @q : Pointer to the queue.
 * @entry : New entry that needs to be added into the queue.
 */ 
int queue_add(queue_t *q, void *entry)
{
    assert(q);

    queue_entry_t *new_entry = (queue_entry_t *) malloc(sizeof (queue_entry_t));

    if (!new_entry)
    {
        LOG_ERR("Failed to allocate memory for the new entry.");
        return -1;
    }

    new_entry->data = entry;
    new_entry->next = NULL;

    if (queue_empty(q))
    {
        q->front = q->rear = new_entry;
    }
    else
    {
        q->rear->next = new_entry;
        q->rear = q->rear->next;
    }

    return 0;
}

/*
 * Remove entry at the front of the queue and return its data part.
 *
 * @q : Queue.
 */
void *queue_remove(queue_t *q)
{
    assert(q);

    if (queue_empty(q))
    {
        /*
         * How can we differentiate between,
         * 1. User has enter NULL as a data and this is the only entry in the queue.
         * 2. Queue is empty.
         *
         * In both the cases we are returing "NULL".
         */
        return NULL;
    }

    queue_entry_t *entry = q->front;
    assert(entry);
    void *data = entry->data;

    q->front = q->front->next;
    free(entry);

    return data;
}

/*
 * Print all entries in the queue from front to rear of the queue.
 * ASSUMPTION: All entries have int as their data part.
 */
void queue_print(queue_t *q)
{
    assert(q);

    queue_entry_t *entry = q->front;

    while (entry)
    {
        printf("%d ", *(int *) entry->data);
        entry = entry->next;
    }
}

void queue_destroy(queue_t *q)
{
    assert(q);

    while (!queue_empty(q))
    {
        queue_remove(q);
    }
}

/*
 * Create queue for given number of entries and for each entry accept data from stdin.
 * Return pointer to the queue on success and NULL on failure.
 *
 * @n : Number of entries.
 */
queue_t *queue_create(unsigned int n)
{
    queue_t *q = (queue_t *) malloc(sizeof (queue_t));
    unsigned int i = 0;

    if (!q)
    {
        LOG_ERR("Failed to allocate memory for queue.");
        return NULL;
    }

    queue_init(q);

    for (i = 0; i < n; i++)
    {
        int *entry = (int *) malloc(sizeof (int));

        if (!entry)
        {
            LOG_ERR("Failed to allocate memory for queue entry.");
            goto err;
        }

        scanf("%d", entry);

        if (queue_add(q, entry) != 0)
        {
            goto err;
        }
    }

    return q;

err:
    queue_destroy(q);

    free(q);

    return NULL;
}

#endif //__QUEUE_H__
