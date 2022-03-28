#ifndef __HASH
#define __HASH

struct Cell;
struct hash_Table;

void hash_free(struct hash_Table *hash, void (*release)(void *));
int hashCherche(struct hash_Table *hash,void *donnee);
int HashAdd(struct hash_Table *hash,void *donnee);
struct hash_Table *hash_init(int (*cmp)(void *,void *), int (*hash)(void *));
struct Cell *hash_newcell(void *donnee);


#endif
