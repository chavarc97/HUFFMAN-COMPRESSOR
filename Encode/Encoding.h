#ifndef ENCODING_H
#define ENCODING_H

#include "../hashmap/map.h" //Por estructura

char *encode_text_with_huffman(map *code_map, const char *text);

#endif // ENCODING_H
