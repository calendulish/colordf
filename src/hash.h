#ifndef HASH_H
#define HASH_H

struct hash_t {
	struct hash_t *next;
	char *name;
	char *value;
};

#define HASHSIZE 101
struct hash_t *hashtab[HASHSIZE];

unsigned hash(char *);
struct hash_t *lookup(char *);
struct hash_t *install(char *name, char *value);

#endif /* HASH_H */
