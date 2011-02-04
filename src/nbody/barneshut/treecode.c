/**
 * File:   treecode.c
 * Author: petra
 *
 * Created on 04 Februari 2011, 8:20
 * Based on Joshue E. Barnes
 * http://www.ifa.hawaii.edu/~barnes/treecode/
 */

#include <math.h>
#include <stdio.h>
#include "treecode.h"

/**
 * Find the box size of the tree
 * @param root Root of the tree
 * @param rsize Initial box size
 * @param bodies The bodies
 * @param nbody Number of bodies
 * @return Box size of the tree
 */
int expandBox(cellptr * root, int rsize, bodyptr bodies, int nbody);

/**
 * Compute subcell index for a body in specified cell
 * @param p The body
 * @param q The cell
 * @return Index body p in cell q
 */
int findIndex(bodyptr p, cellptr q);

void treeInit(cellptr * root, bodyptr bodies, int nbody)
{
	bodyptr p;

	/* Foreach bodies */
	for (p = bodies; p < bodies + nbody; p++) {
		/* Insert into tree */
	}
}

void treeFree(cellptr * root){

	nodeptr p;
	if (root != NULL){
		/* Start with the root */
		p = (nodeptr) root;
		while(p != NULL){
			if (Type(p) == CELL){
				
			}
		}
	}
}

void treeInsert(cellptr * root, bodyptr body)
{
	cellptr q, c;
	int qidx, k;
	real qsize;
	q = (*root);
	qidx = findIndex(body, q);

}

int expandBox(cellptr * root, int rsize, bodyptr bodies, int nbody)
{
	real dmax, d;
	bodyptr p;
	int k;

	/* Keep track of max value */
	dmax = 0.0;
	/* Loop over all bodies */
	for (p = bodies; p < bodies + nbody; p++)
		/* Loop over each dimension */
		for (k = 0; k < NDIM; k++) {
			/* Find distance to midpoint */
			d = fabsf(Pos(p)[k] - Pos(*root)[k]);
			/* Max d */
			dmax = (d > dmax) ? d : dmax;
		}
	while (rsize < 2 * dmax)
		rsize *= 2;
	return rsize;
}

int findIndex(bodyptr p, cellptr q)
{
	int idx, k;
	/* Accumulate the subcell index */
	idx = 0;
	/* Loop over dimensions */
	for (k = 0; k < NDIM; k++)
		/* If beyond midpoint */
		if (Pos(q)[k] <= Pos(p)[k])
			/* Skip over subcells */
			idx += NSUB >> (k + 1);
	return idx;
}