
// HUFFMAN LIBRARY TO COMPRESS AND DECOMPRESS FILES
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "huffman.h"

// ********************************************************************************
// ************************** HUFFMAN TREE FUNCTIONS ******************************
// ********************************************************************************

typedef struct H_node {
    int value;
    int freq;
    struct H_node *left;
    struct H_node *right;
} H_node;

// Huffman tree
typedef struct Huffman
{
    H_node *root;

} Huffman;

// ********************************************************************************
// ************************** HUFFMAN TREE FUNCTIONS ******************************
// ********************************************************************************
// Create a new node
H_node *new_node(int value, int freq, H_node *left, H_node *right) {
    H_node *node = (H_node *) malloc(sizeof(H_node));
    node->value = value;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Free a node
void free_node(H_node *node) {
    if (node == NULL) return;
    free_node(node->left);
    free_node(node->right);
    free(node);
}

// Compare two nodes

// build a Huffman tree



