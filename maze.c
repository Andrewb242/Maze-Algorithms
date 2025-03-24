
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "eller.h"


/*
 * Parse command line arguments and initialize maze parameters
 * Expected format: ./eller width height [output_file]
 * Returns 0 on success, non-zero on failure
 */
int parse_arguments(int argc, char *argv[], int *width, int *height, char **output_file) {
	// Set default values
	*output_file = NULL;

	// Check for minimum required arguments (program name, width, height)
	if (argc < 3) {
		fprintf(stderr, "Usage: %s width height [output_file]\n", argv[0]);
		return 1;
	}

	// Parse width
	*width = atoi(argv[1]);
	if (*width <= 0) {
		fprintf(stderr, "Error: Width must be a positive integer\n");
		return 1;
	}

	// Parse height
	*height = atoi(argv[2]);
	if (*height <= 0) {
		fprintf(stderr, "Error: Height must be a positive integer\n");
		return 1;
	}

	// Parse optional output file
	if (argc >= 4) {
		*output_file = argv[3];
	}

	return 0;
}



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
}

void maze_free(maze_t* maze) {

        for (int i=0; i < maze->max_sets; i++) {
                set_free(maze->sets[i]);
        }
}

int main(int argc, char *argv[]) {
        // Seed random number generator
        srand(time(NULL));

        // Parse command line arguments
        int width, height;
        char *output_file;

        if (parse_arguments(argc, argv, &width, &height, &output_file) != 0) {
                return 1;  // Exit if argument parsing failed
        }

        printf("Generating maze with width %d and height %d\n", width, height);
        if (output_file) {
                printf("Output will be written to %s\n\n", output_file);
        } else {
                printf("Output will be written to standard output\n\n");
        }

        // Initialize the maze

        maze_t new_maze;
        new_maze.width = width;
        new_maze.height = height;
        maze_init(&new_maze);
        printf("Initialized maze:\n");
        print_maze(&new_maze);


	// Prompt user for algorithm type
	int alg_type = 0;
	printf("1. Eller's\n");
	printf("Input maze generation algorithm number: ");
	if (scanf("%d", &alg_type) == 0) {
		perror("Scan failed\n");	
		return 1;
	}

	switch (alg_type) {
		case 1:
			printf("Eller's algorithm selected.\n");
			ellers(&new_maze);
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

void print_maze(maze_t* maze) {
        if (!maze || !maze->cells) {
                printf("Error: Invalid maze\n");
                return;
        }

        // Print top border
        for (int x = 0; x < maze->width; x++) {
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
        for (int x = 0; x < maze->width; x++) {
                printf("+---");
        }
        printf("+\n");
}

