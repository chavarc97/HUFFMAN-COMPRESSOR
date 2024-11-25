#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap/map.c"
#include "ColaDePrioridad/priority.c"
#include "huffmanT/huffmanTree.c"

// ****************************************************************************************************
// Defines
#define BUCKET_SIZE 10
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define RESET "\033[0m"
// Global variables
FILE *file;

// Function prototypes
map *create_freq_map(char *file);
void print_freq_map(map *freq_m);
PriorityQueue *create_priority_queue_from_map(map *freq_m);
void print_priority_queue(PriorityQueue *pq);
void print_freq_map_binary(map *freq_m);
void print_asterisks();
// ****************************************************************************************************

int main(int argc, char const *argv[])
{
    printf("\n");
    printf(YELLOW "██╗  ██╗██╗   ██╗███████╗███████╗███╗   ███╗ █████╗ ███╗   ██╗\n\
██║  ██║██║   ██║██╔════╝██╔════╝████╗ ████║██╔══██╗████╗  ██║\n\
███████║██║   ██║█████╗  █████╗  ██╔████╔██║███████║██╔██╗ ██║\n\
██╔══██║██║   ██║██╔══╝  ██╔══╝  ██║╚██╔╝██║██╔══██║██║╚██╗██║\n\
██║  ██║╚██████╔╝██║     ██║     ██║ ╚═╝ ██║██║  ██║██║ ╚████║\n\
╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝     ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝\n\
██████╗ ██████╗ ██████╗ ██╗███╗   ██╗ ██████╗\n\
██╔════╝██╔═══██╗██╔══██╗██║████╗  ██║██╔════╝\n\
██║     ██║   ██║██║  ██║██║██╔██╗ ██║██║  ███╗\n\
██║     ██║   ██║██║  ██║██║██║╚██╗██║██║   ██║\n\
╚██████╗╚██████╔╝██████╔╝██║██║ ╚████║╚██████╔╝\n\
╚═════╝ ╚═════╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝ ╚═════╝ \n\n" RESET);
    // Crear un mapa de frecuencias
    map *freq_m = create_freq_map("test.txt");

    if (freq_m != NULL)
    {
        print_asterisks(); // Print a line of asterisks
        printf(RED "*%30sMAPA DE FRECUENCIAS%34s", "", "*" RESET);
        print_asterisks(); // Print a line of asterisks
        printf("\n");

        print_freq_map(freq_m);

        // Crear una cola de prioridad con el mapa de frecuencias
        PriorityQueue *pq = create_priority_queue_from_map(freq_m);
        print_asterisks(); // Print a line of asterisks
        printf(RED "*%22sFRECUENCIAS EN ORDEN ASCENDENTE%26s", "", "*");
        print_asterisks(); // Print a line of asterisks
        printf("\n");
        print_priority_queue(pq);

        // Create Huffman tree from priority queue
        print_asterisks(); // Print a line of asterisks
        printf(RED "*%30sHUFFMAN TREE BUILD%35s", "", "*" RESET);
        print_asterisks(); // Print a line of asterisks
        printf("\n");
        HuffmanTree *huffman_tree = huffman_create_tree(pq);

        if (huffman_tree != NULL)
        {
            // Construct a dictionary from the Huffman tree codes and print it
            huffman_print_codes(huffman_tree);

            map *dict = create_code_map(huffman_tree);
            print_asterisks(); // Print a line of asterisks
            printf(RED "*%29sCODES TO DICTIONARY%35s", "", "*" RESET);
            print_asterisks(); // Print a line of asterisks
            printf("\n");
            print_freq_map_binary(dict);
            huffman_destroy_tree(huffman_tree);
        }
        else
        {
            printf("Error: Could not create Huffman tree\n");
        }
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
        perror("Error al abrir el archivo");
        return NULL;
    }

    map *freq_m = map_create(BUCKET_SIZE, char_hash, char_equals);

    // Contar frecuencias en el archivo
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c >= 0 && c <= 127)
        {
            char temp_char = (char)c;
            int *freq = (int *)map_get(freq_m, &temp_char);

            if (freq == NULL)
            {
                char *char_key = malloc(sizeof(char));
                *char_key = temp_char;
                freq = malloc(sizeof(int));
                *freq = 1;
                map_put(freq_m, char_key, freq);
            }
            else
            {
                (*freq)++;
            }
        }
    }
    fclose(file);
    return freq_m;
}

void print_freq_map(map *freq_m)
{
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        node *n = freq_m->hashTable[i];
        while (n != NULL)
        {
            char c = *(char *)n->key;
            int freq = *(int *)n->value;
            if (c == ' ')
            {
                printf("  'SPACE': %6d\n", freq);
            }
            else if (c == '\n')
            {
                printf("  'NEWLINE': %6d\n", freq);
            }
            else
            {
                printf("  '%c': %10d\n", c, freq);
            }
            n = n->next;
        }
    }
}

void print_freq_map_binary(map *freq_m)
{
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        node *n = freq_m->hashTable[i];
        while (n != NULL)
        {
            char c = *(char *)n->key;
            char *code = (char *)n->value;
            if (c == ' ')
            {
                printf("  'SPACE': %6s\n", code);
            }
            else if (c == '\n')
            {
                printf("  'NEWLINE': %6s\n", code);
            }
            else
            {
                printf("  '%c': %10s\n", c, code);
            }
            n = n->next;
        }
    }
}

PriorityQueue *create_priority_queue_from_map(map *freq_m)
{
    PriorityQueue *pq = pq_create();

    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        node *n = freq_m->hashTable[i];
        while (n != NULL)
        {
            // Allocate new memory for the character
            char *char_key = malloc(sizeof(char));
            *char_key = *(char *)n->key;

            // Push to priority queue
            pq_push(pq, char_key, *(int *)n->value);

            n = n->next;
        }
    }
    return pq;
}
/*vasado en 'print_freq_map'*/
void print_priority_queue(PriorityQueue *pq)
{
    PQNode *temp = pq->front;
    /*Si la cola no esta vacia continua verificando con el bucle*/
    while (temp != NULL)
    {
        /*Guarda la frecuencia y el caracter(contando linea nueva y espacios)*/
        char c = *(char *)temp->data;
        int freq = temp->priority;
        /*Verifica que tipo de caracter esta usando y lo imprime,
        luego se llama a pq_pop que lo elimina de la lista*/
        if (c == ' ')
        {
            printf("  'SPACE': %6d\n", freq);
        }
        else if (c == '\n')
        {
            printf("  'NEWLINE': %6d\n", freq);
        }
        else
        {
            printf("  '%c': %10d\n", c, freq);
        }
        /*mueve al siguiente valor*/
        temp = temp->next;
    }
}

void print_asterisks()
{
    printf(RED "\n");
    for (int i = 0; i < 80; i++)
    {
        printf("*");
    }
    printf("\n" RESET);
}