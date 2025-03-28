
#include <stdlib.h>
#include <stdio.h>
#include "eller.h"

// Create a new set
set_t* set_create() {
	set_t* new_set = (set_t*)malloc(sizeof(set_t));
	if (!new_set) {
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	new_set->head = NULL;
	new_set->member_count = 0;
	return new_set;
}

// Add a node to a set
void set_add(set_t* set, node_t* node) {
	
	node_t* cur = set->head;

	if (!cur) {
		set->head = node;
	} else {
		while (cur->next) {
			cur = cur->next;	
		}
		cur->next = node;
	}

	node->set = set;
	node->set_id = set->id;
	node->next = NULL;
	set->member_count++;
}

// Append all nodes from Set B to Set A, freeing the Set B pointer
set_t* set_union(set_t* set_a, set_t* set_b) {
	
	node_t* cur = set_b->head;
	node_t* prev = NULL;

	while (cur) {
		prev = cur;
                cur = cur->next;
		set_add(set_a, prev);
        }

	set_b->head = NULL;
	return set_a;
}

// Remove a node from a set, freeing it in the process
void set_remove(node_t* node) {
	
	if (!node || !node->set) return;
	set_t* set = node->set;

	node_t* cur = set->head;
	node_t* prev = NULL;

	while (cur && cur->next && cur != node) {
		prev = cur;
		cur = cur->next;
	}
	
	if (!cur) {
		return;
	}

	if (prev) {
		prev->next = cur->next;
	} else {
		set->head = cur->next;
	}

	set->member_count--;
	free(node);
}

// Check if a set contains a specific node
int set_contains(set_t* set, node_t* node) {
	return (node && node->set == set);
}

// Free a set and all nodes within the set
void set_free(set_t* set) {

	if (!set) return;
	
	node_t* cur = set->head;
	node_t* prev = NULL;
	
	while (cur) {
		prev = cur;
		cur = cur->next;
		free(prev);
	}

	free(set);
}
