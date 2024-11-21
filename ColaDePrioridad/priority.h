#ifndef PRIORITY_H
#define PRIORITY_H

typedef struct PQNode {
    void *data;
    int priority;
    struct PQNode *next;
} PQNode;

typedef struct PriorityQueue {
    PQNode *front;
} PriorityQueue;

PriorityQueue *pq_create();
void pq_push(PriorityQueue *pq, void *data, int priority);
void *pq_pop(PriorityQueue *pq);
int pq_is_empty(PriorityQueue *pq);

#endif