# Huffman Coding Implementation

A C implementation of Huffman coding for text file compression. This project provides a complete solution for encoding and decoding text using Huffman's algorithm, featuring a custom hashmap implementation and priority queue for efficient data management.

## Features

- Text file compression using Huffman coding algorithm
- Custom hashmap implementation for frequency counting and code storage
- Priority queue for efficient Huffman tree construction
- Support for ASCII characters, spaces, and newlines
- Visual representation of the Huffman tree building process
- Encoding and decoding capabilities

## Project Structure

```bash
.
├── ColaDePrioridad/        # Priority Queue implementation
│   ├── priority.c
│   └── priority.h
├── Encode/                 # Encoding/Decoding implementation
│   ├── Encoding.c
│   └── Encoding.h
├── hashmap/               # Custom hashmap implementation
│   ├── map.c
│   └── map.h
├── huffmanT/             # Huffman tree implementation
│   ├── huffmanTree.c
│   └── huffmanTree.h
├── .gitignore            # Git ignore file
├── main                  # Compiled executable
├── main.c               # Main program logic and UI
├── README.md            # Project documentation
├── test.txt            # Sample input file
└── TODO.md             # Project tasks and todos
```

## Dependencies

- Standard C libraries:
  - stdio.h
  - stdlib.h
  - string.h

## Usage

1. Compile the project:

```bash
gcc main.c -o huffman
```

2. Run the program:

```bash
./huffman
```

3. The program will:
   - Read the input from `test.txt`
   - Display character frequencies
   - Show the Huffman tree construction process
   - Generate Huffman codes for each character
   - Encode the input text
   - Decode the encoded text back to its original form

## Implementation Details

### Data Structures

1. **Hashmap (`hashmap/map.c`)**

   - Custom implementation for storing character frequencies and codes
   - Collision handling through chaining
   - Dynamic bucket allocation
2. **Priority Queue (`ColaDePrioridad/priority.c`)**

   - Min-heap implementation for Huffman tree construction
   - Maintains nodes sorted by frequency
   - Supports custom data types
3. **Huffman Tree (`huffmanT/huffmanTree.c`)**

   - Binary tree structure for code generation
   - Supports character storage and frequency information
   - Includes tree traversal for code generation

### Key Functions

- `create_freq_map`: Generates frequency map from input text
- `huffman_create_tree`: Constructs Huffman tree from priority queue
- `encode_file_with_huffman`: Encodes text file using generated Huffman codes
- `decode_text_with_huffman`: Decodes Huffman-encoded text

## Output Format

The program provides detailed output including:

- Frequency map of characters
- Priority queue ordering
- Huffman tree construction steps
- Generated Huffman codes
- Encoded binary string
- Decoded text verification

## Memory Management

The implementation includes proper memory management with:

- Dynamic allocation for all data structures
- Proper cleanup of allocated memory
- Memory leak prevention

## Limitations

- Currently supports ASCII characters only
- Input file must be named `test.txt`
- Encoded output is represented as a binary string (not compressed binary file)
