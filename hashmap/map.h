#ifndef MAP_H_
#define MAP_H_

typedef int boolean;
#define TRUE 1
#define FALSE 0

#define BUCKET_SIZE 10

typedef int (*hash_func)(void *);
typedef boolean (*equals_func)(void *, void *);
typedef struct map_str map;

 struct node_str {
    void * key, * value;
    struct node_str * next;
  };
  
  typedef struct node_str node;
  
  typedef struct map_str {
    hash_func hash;
    equals_func key_equals;
    int M, size;
    node ** hashTable;
  } map_str;



map *map_create(int m, hash_func, equals_func);
int map_size(map *m);
void map_put(map *m, void *key, void *value);
boolean map_contains(map *m, void *key);
void *map_get(map *m, void *key);
int char_hash(void *key);
boolean char_equals(void* key1, void* key2);

#endif /* MAP_H_ */
