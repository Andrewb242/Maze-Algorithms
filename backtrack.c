/*
 * backtrack.c -  implementation of backtracking algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "backtrack.h"
#include "pos.h"



void backtrack(maze_t* maze, int print) {
	
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

					if (print) printf("Current Position: (%d,%d)\n", pos.cur_node->x, pos.cur_node->y);

					if (pos.id == 0) return;

					if (print) printf("Backtracking...\n");

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
				if (print) printf("New position: (%d,%d)\n", pos.cur_node->x, pos.cur_node->y);
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
		if (print) {
			printf("Itteration #%d\n", itteration);
			print_maze(maze);
		}
		itteration++;
	}
}
