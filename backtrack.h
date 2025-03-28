/*
 * backtrack.h - Header file for backtracking algorithm for maze generation
 */

#include "maze.h"
#include "set.h"

#ifndef BACKTRACK_H
#define BACKTRACK_H

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

void calc_pos_data(maze_t* maze, pos_data_t* pos);
void backtrack(maze_t* maze, int print);

#endif /* BACKTRACK_H */
