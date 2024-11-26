#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Encoding.h"

char *encode_file_with_huffman(map *code_map, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    // Calcula un tamaño inicial para el buffer
    int buffer_size = 1024;
    char *encoded_text = (char *)malloc(buffer_size);
    if (encoded_text == NULL) {
        printf("Error al asignar memoria para el texto codificado\n");
        fclose(file);
        return NULL;
    }
    encoded_text[0] = '\0'; // Inicializa como cadena vacía

    char c;
    while ((c = fgetc(file)) != EOF) {
        // Busca el código en el mapa
        char *code = (char *)map_get(code_map, &c);
        if (code == NULL) {
            printf("Error: No se encontró el código para '%c'\n", c);
            free(encoded_text);
            fclose(file);
            return NULL;
        }

        // Verifica si hay suficiente espacio en el buffer
        if (strlen(encoded_text) + strlen(code) + 1 > buffer_size) {
            buffer_size *= 2;
            encoded_text = (char *)realloc(encoded_text, buffer_size);
            if (encoded_text == NULL) {
                printf("Error al redimensionar el buffer\n");
                fclose(file);
                return NULL;
            }
        }

        // Agrega el código al texto codificado
        strcat(encoded_text, code);
    }

    fclose(file);
    return encoded_text;
}
