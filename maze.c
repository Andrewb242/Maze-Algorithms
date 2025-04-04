
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "eller.h"
#include "kruskal.h"
#include "backtrack.h"

	
// Maze Initialization
void maze_init(maze_t* maze){

        // Initialize maze
        int area = maze->width * maze->height;
        maze->max_sets = area;
        maze->set_count = 0;

        maze->sets = (set_t**)malloc(sizeof(set_t*) * area);
        maze->cells = (node_t**)malloc(sizeof(node_t*) * area);

        // Initialize sets and cells
        int x = 0, y = 0;
        for (int i = 0; i < area; i++) {

                // Initialize new set
                set_t* new_set = set_create();
                new_set->id = i;
                new_set->head = NULL;
                new_set->member_count = 0;

                // Initialize new node
                node_t* new_node = (node_t*)malloc(sizeof(node_t));
                new_node->up = NULL;
                new_node->down = NULL;
                new_node->left = NULL;
                new_node->right = NULL;
                new_node->x = x;
                new_node->y = y;
                new_node->visited = 0;
                x++;

                if (x > maze->width - 1) {
                        y++;
                        x = 0;
                }

                // insert into the set
                set_add(new_set, new_node);

                // Update cells and sets in maze
                maze->cells[i] = new_node;
                maze->sets[i] = new_set;
                maze->set_count++;
        }

	maze->start = maze->cells[0];
	maze->end = maze->cells[maze->set_count - 1];
}

void maze_free(maze_t* maze) {

        for (int i=0; i < maze->max_sets; i++) {
                set_free(maze->sets[i]);
        }
}

static int width;
static int height;

int main() {
        // Seed random number generator
        srand(time(NULL));
	
	printf("Input a positive integer for maze width:");
	if (scanf("%d", &width) == 0) return 1;

	printf("Input a positive integer for maze height:");
	if (scanf("%d", &height) == 0) return 1;

        printf("Generating maze with width %d and height %d\n", width, height);

        // Initialize the maze

        maze_t new_maze;
        new_maze.width = width;
        new_maze.height = height;
        maze_init(&new_maze);
        printf("Initialized maze:\n");
        print_maze(&new_maze);


	// Prompt user for algorithm type
	int alg_type = 0;
	printf("0. Time Comparison\n");
	printf("1. Backtrack\n");
	printf("2. Eller's\n");
	printf("3. Kruskal's\n");
	printf("Input maze generation algorithm number: ");
	if (scanf("%d", &alg_type) == 0) {
		perror("Scan failed\n");	
		return 1;
	}

	switch (alg_type) {
		case 0:
			printf("Time Comparison selected...\n");
			maze_free(&new_maze);
			time_cmp(&backtrack, "Backtrack");
			time_cmp(&ellers, "Eller's");
			time_cmp(&kruskal, "Kruskal's");
			exit(0);
		case 1:
			printf("Backtrack algorithm selected...\n");
			backtrack(&new_maze, 1);
			break;
		case 2:
			printf("Eller's algorithm selected...\n");
			ellers(&new_maze, 1);
			break;
		case 3: printf("Kruskal's Algorithm selected...\n");
			kruskal(&new_maze, 1);
			break;
		default:
			printf("Invalid option.\n");
			maze_free(&new_maze);
			return 1;
	}
		
        // Output the maze
        printf("\nFinal maze:\n");
        print_maze(&new_maze);

        maze_free(&new_maze);

        return 0;
}

void time_cmp(void (*func) (maze_t*, int), char* name) {

	clock_t start, end;
	double cpu_time_used;

	maze_t maze;
	maze.width = width;
	maze.height = height;
	maze_init(&maze);

	start = clock();
	func(&maze, 0);
	end = clock();

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("%s algorithm finished with time %lf seconds\n", name, cpu_time_used);
	maze_free(&maze);
}

void print_maze(maze_t* maze) {
        if (!maze || !maze->cells) {
                printf("Error: Invalid maze\n");
                return;
        }

        // Print top border
	printf("+   ");
        for (int x = 0; x < maze->width - 1; x++) {
                printf("+---");
        }
        printf("+\n");

        // Print rows
        for (int y = 0; y < maze->height; y++) {
                // Print cells and vertical walls
                printf("|");
                for (int x = 0; x < maze->width; x++) {
                        int index = y * maze->width + x;
                        node_t* cell = maze->cells[index];

                        // Print cell content (set ID or space)
                        printf(" %d ", cell->set_id % 10);

                        // Print vertical wall if no right connection
                        if (x < maze->width - 1 && (!cell->right || cell->right->set_id != cell->set_id)) {
                                printf("|");
                        } else {
                                printf(" ");
                        }
                }
                printf("|\n");

                // Print horizontal walls
                if (y < maze->height - 1) {
                        for (int x = 0; x < maze->width; x++) {
                                int index = y * maze->width + x;
                                node_t* cell = maze->cells[index];

                                printf("+");

                                // Print horizontal wall if no down connection
                                if (!cell->down || cell->down->set_id != cell->set_id) {
                                        printf("---");
                                } else {
                                        printf("   ");
                                }
                        }
                        printf("+\n");
                }
        }

        // Print bottom border
        for (int x = 0; x < maze->width - 1; x++) {
                printf("+---");
        }
        printf("+   +\n");
}

