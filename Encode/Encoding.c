#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Encoding.h"

char *encode_file_with_huffman(map *code_map, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return NULL;
    } /* Calcula un tamaño inicial para el buffer */
    int buffer_size = 1024;
    char *encoded_text = (char *)malloc(buffer_size);
    if (encoded_text == NULL)
    {
        printf("Error al asignar memoria para el texto codificado\n");
        fclose(file);
        return NULL;
    }
    encoded_text[0] = '\0'; /* Inicializa como cadena vacía */

    char c;
    while ((c = fgetc(file)) != EOF)
    { /* Busca el código en el mapa */
        char *code = (char *)map_get(code_map, &c);
        if (code == NULL)
        {
            printf("Error: No se encontró el código para '%c'\n", c);
            free(encoded_text);
            fclose(file);
            return NULL;
        } /* Verifica si hay suficiente espacio en el buffer */
        if (strlen(encoded_text) + strlen(code) + 1 > buffer_size)
        {
            buffer_size *= 2;
            encoded_text = (char *)realloc(encoded_text, buffer_size);
            if (encoded_text == NULL)
            {
                printf("Error al redimensionar el buffer\n");
                fclose(file);
                return NULL;
            }
        }

        strcat(encoded_text, code); /* Agrega el código al texto codificado */
    }

    fclose(file);
    return encoded_text;
}

char *decode_text_with_huffman(map *code_map, char *encoded_text)
{
    if (encoded_text == NULL || code_map == NULL)
    {
        return NULL;
    }
    size_t max_length = strlen(encoded_text); /* Asigna espacio para el texto decodificado */
    char *decoded_text = (char *)malloc(max_length + 1);
    if (decoded_text == NULL)
    {
        return NULL;
    }

    char *current_code = (char *)malloc(max_length + 1); /* Buffer para almacenar el código actual que se está construyendo */
    if (current_code == NULL)
    {
        free(decoded_text);
        return NULL;
    }

    size_t decoded_pos = 0;
    size_t i = 0;

    while (encoded_text[i] != '\0')
    {
        size_t code_len = 0;
        boolean found = FALSE;

        while (encoded_text[i] != '\0') /* Intentar construir un código válido */
        {
            current_code[code_len++] = encoded_text[i];
            current_code[code_len] = '\0';

            for (int bucket = 0; bucket < BUCKET_SIZE; bucket++) /* Buscar en todas las entradas del mapa de códigos */
            {
                node *current = code_map->hashTable[bucket];
                while (current != NULL)
                { /* Comparar el código actual con el valor en el mapa */
                    if (strcmp((char *)current->value, current_code) == 0)
                    { /* Se encontró una coincidencia - agregar el caracter correspondiente al texto decodificado */
                        decoded_text[decoded_pos++] = *(char *)current->key;
                        found = TRUE;
                        break;
                    }
                    current = current->next;
                }
                if (found)
                    break;
            }

            if (found)
                break;
            i++;
        }

        if (!found)
        { /* Si no se pudo encontrar un código válido, limpiar y devolver NULL */
            free(decoded_text);
            free(current_code);
            return NULL;
        }

        i++; /* Mover al siguiente bit después de encontrar un código válido */
    }

    decoded_text[decoded_pos] = '\0';
    free(current_code);

    return decoded_text;
}
