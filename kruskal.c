
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "set.h"
#include "kruskal.h"

void kruskal(maze_t* maze, int print) {

	// Initialize position
	pos_data_t pos;

	pos.id = 0;
	pos.cur_node = maze->cells[0];
	pos.cur_set = pos.cur_node->set;

	int new_id = 0;

	while (maze->set_count > 1) {
		
		// Random index
		new_id = rand() % maze->max_sets;
		pos.id = new_id;
		pos.cur_node = maze->cells[new_id];
		pos.cur_set = pos.cur_node->set;
		calc_pos_data(maze, &pos);

		if (pos.prob_thresh > 100) {
			// Cannot merge either way
			continue;
		}

		if (pos.above_set && pos.above_set != pos.cur_set && rand() % 100 + 1 < pos.prob_thresh) {
			set_union(pos.cur_set, pos.above_set);
			maze->set_count--;
			node_t* above_node = maze->cells[pos.above_id];
			pos.cur_node->up = above_node;
			above_node->down = pos.cur_node;
			if (print) {
				printf("Merged up at (%d,%d).\n", pos.cur_node->x, pos.cur_node->y);
				print_maze(maze);
			}

		} else if (pos.below_set && pos.below_set != pos.cur_set && rand() % 100 + 1 < pos.prob_thresh) {
			set_union(pos.cur_set, pos.below_set);
			maze->set_count--;
			node_t* below_node = maze->cells[pos.below_id];
			pos.cur_node->down = below_node;
			below_node->up = pos.cur_node;
			if (print) {
				printf("Merged down at (%d,%d).\n", pos.cur_node->x, pos.cur_node->y);
				print_maze(maze);
			}

		} else if (pos.left_set && pos.left_set != pos.cur_set && rand() % 100 + 1 < pos.prob_thresh) {
			set_union(pos.cur_set, pos.left_set);
			maze->set_count--;
			node_t* left_node = maze->cells[pos.left_id];
			pos.cur_node->left = left_node;
			left_node->right = pos.cur_node;
			if (print) {
				printf("Merged left at (%d,%d).\n", pos.cur_node->x, pos.cur_node->y);
				print_maze(maze);
			}

		} else if (pos.right_set && pos.right_set != pos.cur_set && rand() % 100 + 1 < pos.prob_thresh) {
			set_union(pos.cur_set, pos.right_set);
			maze->set_count--;
			node_t* right_node = maze->cells[pos.right_id];
			pos.cur_node->right = right_node;
			right_node->left = pos.cur_node;
			if (print) {
				printf("Merged right at (%d,%d).\n", pos.cur_node->x, pos.cur_node->y);
				print_maze(maze);
			}
		}
		
	}
}
