#include "priority.h"
#include <stdlib.h>

PriorityQueue *pq_create() {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->front = NULL;
    return pq;
}

/*Este bloque de código inserta un nuevo nodo en la cola de prioridad, 
manteniendo el orden basado en la prioridad (de menor a mayor).*/
void pq_push(PriorityQueue *pq, void *data, int priority) 
{
    /**/
    PQNode *newNode = (PQNode *)malloc(sizeof(PQNode));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    /*cuando la cola esta vacia el nodo 
    o cuando el nod tiene menor prioriedad que el nodo inicial
    se coloca al inicio*/
    if (pq->front == NULL || pq->front->priority > priority) 
    {
        newNode->next = pq->front;
        pq->front = newNode;
    } 
    /*Caso en el que el nodo no va al inicio (igual o mayor frecuencia)*/
    else 
    {
        /*Regresa al inicio de la cola*/
        PQNode *temp = pq->front;
        /*Busca posicion en la que el nodo es menor que la prioiedad 
        actual de la cola*/
        while (temp->next != NULL && temp->next->priority <= priority) 
        {
            temp = temp->next;
        }
        /*agrega el nodo en la pocicion correcta*/
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void *pq_pop(PriorityQueue *pq) 
{
    if (pq->front == NULL) 
    {
        return NULL;
    }
    /*Si la cola esta vacia se crea un puntero  al primero nodo de la cola */
    PQNode *temp = pq->front;
    /*Actualiza para que apunte al siguiiente nodo*/
    pq->front = pq->front->next;
    /*Guarda el dato que fue removido*/
    void *data = temp->data;
    free(temp);
    return data;
}
/*Verifica si la cola esta vacía*/
int pq_is_empty(PriorityQueue *pq) 
{
    return pq->front == NULL;
}
