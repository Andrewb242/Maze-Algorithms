
#ifndef MAZE_H
#define MAZE_H

typedef struct set set_t;

typedef struct node {
	struct node* up;
	struct node* down;
	struct node* left;
	struct node* right;
	set_t* set;
	int set_id;
	struct node* next;
	int x, y;
	int visited;
} node_t;

typedef struct maze {
	int width;
	int height;
	node_t** cells;    
	set_t** sets;       
	int set_count;       
	int max_sets;        
	node_t* start;
	node_t* end;
} maze_t;

void time_cmp(void (*func) (maze_t*, int), char* name);
void print_maze(maze_t* maze);

#endif // MAZE_H
