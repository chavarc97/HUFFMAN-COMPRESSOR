#include <stdlib.h>
#include <stdio.h>
#include "huffmanTree.h"

// Helper function to create a new Huffman node
HuffmanNode *create_node(char character, int frequency)
{
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    if (node == NULL)
    {
        printf("Failed to allocate memory for node\n");
        return NULL;
    }
    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to convert PQNode to HuffmanNode
HuffmanNode *pq_node_to_huffman_node(PQNode *pq_node)
{
    if (pq_node == NULL)
        return NULL;
    // Create a new Huffman node with the same data and priority
    return create_node(*(char *)pq_node->data, pq_node->priority);
}

// Create Huffman tree from priority queue
HuffmanTree *huffman_create_tree(PriorityQueue *pq)
{
    // check if the priority queue is empty
    if (pq_is_empty(pq))
    {
        return NULL;
    }

    HuffmanTree *tree = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    if (tree == NULL)
    {
        return NULL;
    }

    // Create a temporary queue to store Huffman nodes
    PriorityQueue *temp_queue = pq_create();

    // First, convert all PQNodes to HuffmanNodes
    while (pq->front != NULL)
    {
        char *data = (char *)pq->front->data;
        int freq = pq->front->priority;
        HuffmanNode *leaf = create_node(*data, freq);

        // Store the HuffmanNode pointer as the data
        pq_push(temp_queue, leaf, freq);
        pq_pop(pq);
    }

    // Build the tree from the temporary queue
    while (temp_queue->front != NULL && temp_queue->front->next != NULL)
    {
        // Get two nodes with lowest frequencies
        HuffmanNode *left = (HuffmanNode *)temp_queue->front->data;
        int freq1 = temp_queue->front->priority;
        pq_pop(temp_queue);

        HuffmanNode *right = (HuffmanNode *)temp_queue->front->data;
        int freq2 = temp_queue->front->priority;
        pq_pop(temp_queue);

        // Create a new internal node
        HuffmanNode *internal = create_node('\0', freq1 + freq2);
        internal->left = left;
        internal->right = right;

        // Add the new internal node back to the queue
        pq_push(temp_queue, internal, internal->frequency);

        // Debug print
        printf("Created internal node with freq %d (left: '%c'-%d, right: '%c'-%d)\n",
               internal->frequency,
               left->character ? left->character : '#',
               left->frequency, 
               right->character ? right->character : '#',
               right->frequency);
    }

    // The last remaining node is the root
    if (temp_queue->front != NULL)
    {
        tree->root = (HuffmanNode *)temp_queue->front->data;
    }
    else
    {
        tree->root = NULL;
    }

    // Free the temporary queue structure (but not the nodes)
    free(temp_queue);

    return tree;
}

// Helper function to print the codes of the Huffman tree
void print_codes_recursive(HuffmanNode *node, char *code, int depth)
{
    if (node == NULL)
        return;

    // If this is a leaf node, print the character and its code
    if (node->left == NULL && node->right == NULL)
    {
        code[depth] = '\0';
        if (node->character == ' ')
        {
            printf("  SPACE: %6s\n", code);
        }
        else if (node->character == '\n')
        {
            printf("  NEWLINE: %6s\n", code);
        }
        else
        {
            printf("  '%c': %10s\n", node->character, code);
        }
        return;
    }

    // Traverse left
    if (node->left)
    {
        code[depth] = '0';
        print_codes_recursive(node->left, code, depth + 1);
    }

    // Traverse right
    if (node->right)
    {
        code[depth] = '1';
        print_codes_recursive(node->right, code, depth + 1);
    }
}

// Print the codes of the Huffman tree
void huffman_print_codes(HuffmanTree *tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        printf("Empty Huffman tree!\n");
        return;
    }

    char code[100]; // Buffer to store codes
    printf("\nHuffman Codes:\n");
    print_codes_recursive(tree->root, code, 0);
}

// Helper function to destroy nodes recursively
void destroy_node_recursive(HuffmanNode *node)
{
    if (node == NULL)
        return;

    destroy_node_recursive(node->left);
    destroy_node_recursive(node->right);
    free(node);
}

// Destroy Huffman tree and free memory
void huffman_destroy_tree(HuffmanTree *tree)
{
    if (tree == NULL)
        return;

    destroy_node_recursive(tree->root);
    free(tree);
}

// Create a dictionary from the Huffman tree
void create_map_recursive(HuffmanNode *node, char *code, int depth, map *code_map)
{
    if (node == NULL)
        return;

    // If this is a leaf node, insert the character and its code into the map
    if (node->left == NULL && node->right == NULL)
    {
        code[depth] = '\0';
        char *char_key = malloc(sizeof(char));
        *char_key = node->character;
        char *code_value = malloc(strlen(code) + 1);
        strcpy(code_value, code);
        map_put(code_map, char_key, code_value);
        return;
    }

    // Traverse left
    if (node->left)
    {
        code[depth] = '0';
        create_map_recursive(node->left, code, depth + 1, code_map);
    }

    // Traverse right
    if (node->right)
    {
        code[depth] = '1';
        create_map_recursive(node->right, code, depth + 1, code_map);
    }
}

map* create_code_map(HuffmanTree *tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        return NULL;
    }

    map *code_map = map_create(BUCKET_SIZE, char_hash, char_equals);
    char code[100]; // Buffer to store codes
    create_map_recursive(tree->root, code, 0, code_map);
    return code_map;
}
