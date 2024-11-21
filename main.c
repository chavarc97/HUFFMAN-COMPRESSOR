#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap/map.c"

// ****************************************************************************************************
// defines
#define BUCKET_SIZE 10

// global variables
FILE *file;

// Function prototypes
map *create_freq_map(char *file);
void print_freq_map(map *freq_m);
PriorityQueue *create_priority_queue_from_map(map *freq_m);
void print_priority_queue(PriorityQueue *pq);
// ****************************************************************************************************

int main(int argc, char const *argv[])
{

    // create a frequency map of the characters in the file
    map *freq_m = create_freq_map("test.txt");

    // print the frequency map
    if (freq_m != NULL)
    {
        // print the frequency map
        print_freq_map(freq_m);
    }

    return 0;
}

// ****************************************************************************************************
// Function definitions
// ****************************************************************************************************

map *create_freq_map(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    map *freq_m = map_create(BUCKET_SIZE, char_hash, char_equals);

    // iterate over the file and count the frequency of each character
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c >= 0 && c <= 127) {
            // Create temporary key with current character
            char temp_char = (char)c;
            
            // Try to get existing frequency using temp_char
            int *freq = (int *)map_get(freq_m, &temp_char);

            if (freq == NULL) {
                // Character not found - create new entry
                char *char_key = malloc(sizeof(char));
                *char_key = temp_char;
                freq = malloc(sizeof(int));
                *freq = 1;
                map_put(freq_m, char_key, freq);
            } else {
                // Character found - just increment frequency
                (*freq)++;
            }
        }
    }
    fclose(file);
    return freq_m;
}

void print_freq_map(map *freq_m)
{
    printf("Character Frequencies:\n");
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        node *n = freq_m->hashTable[i];
        if (n != NULL)
        {
            while (n != NULL)
            {
                char c = *(char *)n->key;
                int freq = *(int *)n->value;
                if (c == ' ')
                {
                    printf("  ' ': %d\n", freq);
                }
                else if (c == '\n')
                {
                    printf("  'NEWLINE': %d\n", freq);
                }
                else
                {
                    printf("  '%c': %d\n", c, freq);
                }
                n = n->next;
            }
        }
    }
}
PriorityQueue *create_priority_queue_from_map(map *freq_m)
{
    /*Crea una cola de prioridad vacía*/
    PriorityQueue *pq = pq_create();
    /*Agrega cada elemento en la cola de prioridad*/
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        node *n = freq_m->hashTable[i];
        /*Envia cada valor del mapa a pq_push para ser ordenado*/
        while (n != NULL)
        {
            char *char_key = n->key;
            int *value = n->value;
            pq_push(pq, char_key, *value);
            n = n->next;
        }
    }
    /*Regresa la cola ya ordenada*/
    return pq;
}
/*vasado en 'print_freq_map'*/
void print_priority_queue(PriorityQueue *pq)
{
    /*Si la cola no esta vacia continua verificando con el bucle*/
    while (!pq_is_empty(pq))
    {
        /*Guarda la frecuencia y el caracter(contando linea nueva y espacios)*/
        char c = *(char *)pq->front->data;
        int freq = pq->front->priority;
        /*Verifica que tipo de caracter esta usando y lo imprime, 
        luego se llama a pq_pop que lo elimina de la lista*/
        if (c == ' ')
        {
            printf("  ' ': %d\n", freq);
        }
        else if (c == '\n')
        {
            printf("  'NEWLINE': %d\n", freq);
        }
        else
        {
            printf("  '%c': %d\n", c, freq);
        }
        /*elimnina el valor de la lista que ya fue impreso*/
        pq_pop(pq);
    }
}
