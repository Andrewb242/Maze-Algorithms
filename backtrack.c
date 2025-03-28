/*
 * backtrack.c -  implementation of backtracking algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "backtrack.h"

int left_edge(node_t* node) {
	return node->x == 0;
}
int top_edge(node_t* node) {
	return node->y == 0;
}
int right_edge(maze_t* maze, node_t* node) {
	return node->x == maze->width - 1;
}
int bottom_edge(maze_t* maze, node_t* node) {
	return node->x == maze->height - 1;
}

typedef struct pos_data {
	int id;
	int above_id;
       	int below_id;
	int left_id;
	int right_id;
	set_t* above_set;
	set_t* below_set;
	set_t* left_set;
	set_t* right_set;
	node_t* cur_node;
	set_t* cur_set;
	int prob_thresh;
} pos_data_t;

void calc_pos_data(maze_t* maze, pos_data_t* pos) {
	pos->above_id = pos->id - maze->width;
	pos->below_id = pos->id + maze->width;
	pos->left_id = pos->id - 1;
	pos->right_id = pos->id + 1;

	if (pos->above_id >= 0) {
		pos->above_set = maze->cells[pos->above_id]->set;
	} else {
		pos->above_set = NULL;
	}
	
	if (pos->below_id < maze->max_sets) {
		pos->below_set = maze->cells[pos->below_id]->set;
	} else {
		pos->below_set = NULL;
	}

	if (pos->id % maze->width != 0) {
		pos->left_set = maze->cells[pos->left_id]->set;
	} else {
		pos->left_set = NULL;
	}

	if ((pos->id % maze->width) != (maze->width - 1) && pos->right_id < maze->max_sets) {
		pos->right_set = maze->cells[pos->right_id]->set;
	} else {
		pos->right_set = NULL;
	}

	pos->prob_thresh = 0;

	if (!pos->above_set || pos->above_set == pos->cur_set) {
		pos->prob_thresh++;
	}
	if (!pos->below_set || pos->below_set == pos->cur_set) {
		pos->prob_thresh++;
	}
	if (!pos->left_set || pos->left_set == pos->cur_set) {
		pos->prob_thresh++;
	}
	if (!pos->right_set || pos->right_set == pos->cur_set) {
		pos->prob_thresh++;
	}

	pos->prob_thresh = (pos->prob_thresh * 100) / 3;
	pos->prob_thresh == 0 ? pos->prob_thresh = 100 : pos->prob_thresh;
}

void backtrack(maze_t* maze) {
	
	pos_data_t pos;
	pos.id = 0;
	pos.cur_node = maze->cells[pos.id];
	pos.cur_set = pos.cur_node->set;

	pos.above_set = NULL;
	pos.below_set = NULL;
	pos.left_set = NULL;
	pos.right_set = NULL;

	int itteration = 1;

	while (1) {	

		calc_pos_data(maze, &pos);

		while(1) {

			if (pos.prob_thresh > 100) {

				while (pos.prob_thresh > 100) {

					printf("Current Position: (%d,%d)\n", pos.cur_node->x, pos.cur_node->y);

					if (pos.id == 0) return;

					printf("Backtracking...\n");

					if (pos.cur_node->down && !pos.cur_node->down->visited){
						pos.cur_node->visited = 1;
						pos.cur_node = pos.cur_node->down;
						pos.id = pos.below_id;
					}
					else if (pos.cur_node->up && !pos.cur_node->up->visited) {
						pos.cur_node->visited = 1;
						pos.cur_node = pos.cur_node->up;
						pos.id = pos.above_id;
					}
					else if (pos.cur_node->left && !pos.cur_node->left->visited) { 
						pos.cur_node->visited = 1;
						pos.cur_node = pos.cur_node->left;
						pos.id = pos.left_id;
					}
					else if (pos.cur_node->right && !pos.cur_node->right->visited) { 
						pos.cur_node->visited = 1;
						pos.cur_node = pos.cur_node->right;
						pos.id = pos.right_id;
					}

					calc_pos_data(maze, &pos);

				}
				printf("New position: (%d,%d)\n", pos.cur_node->x, pos.cur_node->y);
			}
		
			if (pos.above_set && pos.above_set != pos.cur_set && rand() % 100 + 1 < pos.prob_thresh) {
				set_union(pos.cur_set, pos.above_set);
				node_t* above_node = maze->cells[pos.above_id];
				pos.cur_node->up = above_node;
				above_node->down = pos.cur_node;

				pos.cur_node = above_node; 
				pos.id = pos.above_id;
				break;
			}
				
			if (pos.below_set && pos.below_set != pos.cur_set && rand() % 100 + 1 < pos.prob_thresh) {
				set_union(pos.cur_set, pos.below_set);
				node_t* below_node = maze->cells[pos.below_id];
				pos.cur_node->down = below_node;
				below_node->up = pos.cur_node;

				pos.cur_node = below_node;
				pos.id = pos.below_id;
				break;
			}		

			if (pos.left_set && pos.left_set != pos.cur_set && rand() % 100 + 1 < pos.prob_thresh) {
				set_union(pos.cur_set, pos.left_set);
				node_t* left_node = maze->cells[pos.left_id];
				pos.cur_node->left = left_node;
				left_node->right = pos.cur_node;

				pos.cur_node = left_node;
				pos.id = pos.left_id;
				break;
			}		

			if (pos.right_set && pos.right_set != pos.cur_set && rand() % 100 + 1 < pos.prob_thresh) {
				set_union(pos.cur_set, pos.right_set);
				node_t* right_node = maze->cells[pos.right_id];
				pos.cur_node->right = right_node;
				right_node->left = pos.cur_node;

				pos.cur_node = right_node;
				pos.id = pos.right_id;
				break;
			}
		}
		printf("Itteration #%d\n", itteration);
		print_maze(maze);
		itteration++;
	}
}
