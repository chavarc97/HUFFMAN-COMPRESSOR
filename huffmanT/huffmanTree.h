#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "../ColaDePrioridad/priority.h"
#include "../hashmap/map.h"

// Structure for Huffman Tree Node
typedef struct HuffmanNode {
    char character;         // Character stored in the node (only for leaf nodes)
    int frequency;         // Frequency of the character
    struct HuffmanNode *left;  // Left child
    struct HuffmanNode *right; // Right child
} HuffmanNode;

// Structure for Huffman Tree
typedef struct HuffmanTree {
    HuffmanNode *root;     // Root of the Huffman tree
} HuffmanTree;

// Function prototypes
HuffmanTree *huffman_create_tree(PriorityQueue *pq);
void huffman_print_codes(HuffmanTree *tree);
void huffman_destroy_tree(HuffmanTree *tree);
void create_map_recursive(HuffmanNode *node, char *code, int depth, map *code_map);
map *create_code_map(HuffmanTree *tree);
void destroy_code_map(map *code_map);

#endif