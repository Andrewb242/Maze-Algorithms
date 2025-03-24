
#ifndef SET_H
#define SET_H

typedef struct node node_t;

typedef struct set {
	int id;
	node_t* head;
        int member_count;
} set_t;

// Function prototypes
set_t* set_create();
void set_add(set_t* set, node_t* node);
set_t* set_union(set_t* set_a, set_t* set_b);
void set_remove(node_t* node);
int set_contains(set_t* set, node_t* node);
void set_free(set_t* set);

#endif // SET_H

