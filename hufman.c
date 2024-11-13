
// HUFFMAN LIBRARY TO COMPRESS AND DECOMPRESS FILES

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


