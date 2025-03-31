
#include <stdio.h>
#include "pos.h"

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
