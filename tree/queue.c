#ifndef __QUEUE_H__

typedef struct queue
{
    void *front, *rear;
} queue_t;

void queue_init(queue_t *q)
{
    q.front = q.rear = NULL;
}

int queue_empty(queue_t *q)
{

}

void queue_add(queue_t *q, void *entry)
{
    
}

#endif //__QUEUE_H__
