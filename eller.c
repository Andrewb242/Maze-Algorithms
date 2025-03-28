/*
 * eller.c - Implementation of Eller's algorithm for maze generation
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "eller.h"


void ellers(maze_t* maze, int print) {

        int row = 0;
        int id = 0;
	// Horizontal Combinations
        while (row < maze->height - 1) {

                for (int col = 0; col < maze->width - 1; col++) {

                        node_t* cur_node = maze->cells[id];
                        node_t* next_node = maze->cells[id + 1];
                        set_t* cur_set = cur_node->set;
                        set_t* next_set = next_node->set;

                        if (cur_set && next_set && cur_set != next_set && rand() % 100 + 1 < 50) {
                                // Combine the sets
				maze->sets[next_set->id] = NULL;
                                set_union(cur_set, next_set);
                                maze->set_count--;

                                // Update node pointers
                                cur_node->right = next_node;
                                next_node->left = cur_node;

                        }
                        id++;
                }
                id++;

		if (print) {
			printf("Row %d horozontal combinations complete\n", row);
			print_maze(maze);
		}

		int* set_has_vertical = calloc(maze->max_sets, sizeof(int));

		int temp_id = id;
		for (int col = 0; col < maze->width; col++) {
			node_t* cur_node = maze->cells[temp_id];
			node_t* above_node = maze->cells[temp_id - maze->width];
			set_t* cur_set = cur_node->set;
			set_t* above_set = above_node->set;
			if (cur_set && above_set && cur_set != above_set && rand() % 100 + 1 < 45) {
				// Combine the sets
				maze->sets[cur_set->id] = NULL;
				set_union(above_set, cur_set);
				maze->set_count--;

				// Update node pointers
				cur_node->up = above_node;
				above_node->down = cur_node;

				// Update indication array
				set_has_vertical[above_set->id] = 1;
			}
		temp_id++;
		}

		temp_id = id;
		for (int col = 0; col < maze->width; col++) {

			node_t* above_node = maze->cells[temp_id - maze->width];
			set_t* above_set = above_node->set;

			if (above_set && !set_has_vertical[above_set->id]) {
				node_t* cur_node = maze->cells[temp_id];
				set_t* cur_set = cur_node->set;

				// Combine the sets
				maze->sets[cur_set->id] = NULL;
				set_union(above_set, cur_set);
				maze->set_count--;

				// Update node pointers
				cur_node->up = above_node;
				above_node->down = cur_node;

				// Update indication array
				set_has_vertical[above_set->id] = 1;
			}
			temp_id++;
		}

		free(set_has_vertical);
		if (print) {
			printf("Row %d vertical combinations complete\n", row);
			print_maze(maze);
		}
                row++;
        }
	// Ensure one set on last row
	for (int col = 0; col < maze->width - 1; col++) {

		node_t* cur_node = maze->cells[id];
		node_t* next_node = maze->cells[id + 1];
		set_t* cur_set = cur_node->set;
		set_t* next_set = next_node->set;

		if (cur_set && next_set && cur_set != next_set) {
			// Combine the sets
			maze->sets[next_set->id] = NULL;
			set_union(cur_set, next_set);
			maze->set_count--;

			// Update node pointers
			cur_node->right = next_node;
			next_node->left = cur_node;

		}
		id++;
	}
	
	if (print) {
		printf("Row %d horizontal combinations complete\n", row);
		print_maze(maze);
	}
}

