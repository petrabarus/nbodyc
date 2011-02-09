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
#include <stdlib.h>
#include "treecode.h"
#include "../../utils/boolean.h"

/**
 * Find the box size of the tree
 * @param root Root of the tree
 * @param rsize Initial box size
 * @param bodies The bodies
 * @param nbody Number of bodies
 * @return Box size of the tree
 */
real expandBox(cellptr root, real rsize, bodyptr bodies, int nbody);

/**
 * Compute subcell index for a body in specified cell
 * @param p The body
 * @param q The cell
 * @return Index body p in cell q
 */
int findIndex(bodyptr p, cellptr q);

/**
 * 
 * @param cell
 */
void calculateCenterOfMass(cellptr cell);

void treeInit(cellptr * root, bodyptr bodies, int nbody)
{
	bodyptr p;
	real rootSize = 1.0;
	/* Count the root size */
	rootSize = expandBox(*root, rootSize, bodies, nbody);
	(*root) = treeCreateCell();
	/* Foreach bodies */
	int i = 0;
	for (p = bodies; p < bodies + nbody; p++) {
		/* Insert into tree */
		treeInsert(root, rootSize, p);
	}
	printTree(*root);
	calculateCenterOfMass(*root);
}

void treeFree(cellptr * cell)
{
	int i;

	nodeptr q;
	for (i = 0; i < NSUB; i++) {
		if (Child(*cell)[i] != NULL)
			if (Type(Child(*cell)[i]) == CELL) {
				cellptr a = (cellptr) Child(*cell)[i];
				treeFree(&a);
			}
	}
	free(*cell);
}

void treeInsert(cellptr * root, real rsize, bodyptr body)
{
	cellptr q, c;
	int qidx, k;
	real qsize;
	q = (*root);
	qidx = findIndex(body, q);
	qsize = rsize;
	/* Loop descending tree */
	while (Child(q)[qidx] != NULL) {
		/* If found a body in subcell */
		if (Type(Child(q)[qidx]) == BODY) {
			if (Pos(body)[0] == Pos(Child(q)[qidx])[0] &&
				Pos(body)[1] == Pos(Child(q)[qidx])[1] &&
				Pos(body)[2] == Pos(Child(q)[qidx])[2])
				die("Error\n");
			/* Allocate cell for both   */
			c = treeCreateCell();
			/* And initialize midpoint  */
			for (k = 0; k < NDIM; k++)
				Pos(c)[k] = Pos(q)[k] + (Pos(body)[k] < Pos(q)[k] ? - qsize : qsize) / 4;
			/* Set offset from parent */
			Child(c)[findIndex((bodyptr) Child(q)[qidx], c)] = Child(q)[qidx];
			/* Put old body in cell     */
			Child(q)[qidx] = (nodeptr) c; /* link cell in tree	*/
		}
		/* Advance to next level */
		q = (cellptr) Child(q)[qidx];
		/* Get index to examine	*/
		qidx = findIndex(body, q);
		/* Shrink current cell	*/
		qsize = qsize / 2;
	}
	/* Store root */
	Child(q)[qidx] = (nodeptr) body;
}

cellptr treeCreateCell()
{
	/* TODO: Create free cell pooling */
	cellptr c;
	int i;
	/* Allocate new cell */
	c = (cellptr) malloc(sizeof(cell));
	/* Initialize cell */
	Type(c) = CELL;
	Update(c) = FALSE;
	/* Initialize the children */
	for (i = 0; i < NSUB; i++) {
		Child(c)[i] = NULL;
	}
	return c;
}

real expandBox(cellptr root, real rsize, bodyptr bodies, int nbody)
{
	real dmax, d;
	bodyptr p;
	int k;

	/* Keep track of max value */
	dmax = 0.0;
	/* Loop over all bodies */
	for (p = bodies; p < bodies + nbody; p++) {
		/* Loop over each dimension */
		for (k = 0; k < NDIM; k++) {
			/* Find distance to midpoint */
			d = fabsf(Pos(p)[k] - Pos(root)[k]);
			/* Max d */
			dmax = (d > dmax) ? d : dmax;
		}
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

void calculateCenterOfMass(cellptr cell)
{
	/* Center of mass position */
	vector cmPos;
	vector tempV;
	nodeptr q;
	int i;
	/* Init the cell's total mass */
	Mass(cell) = 0.0;
	/* Init the cell's center of mass position */
	CLRV(cmPos);
	/* Loop over the subnodes */
	for (i = 0; i < NSUB; i++) {
		/* Skipping empty child nodes */
		if ((q = Child(cell)[i]) != NULL) {
			/* If node is a cell */
			if (Type(q) == CELL)
				/* Recursively do the same */
				calculateCenterOfMass((cellptr) q);
			/* Accumulate total mass */
			Mass(cell) = Mass(q);
			/* Accumulate center of mass */
			ADDMULVS(cmPos, Pos(q), Mass(q));
		}
	}
	/* Usually, cell has mass */
	if (Mass(cell) > 0.0) {
		/* Find center of mass position */
		DIVVS(cmPos, cmPos, Mass(cell));
	} else { /* If no mass inside */
		SETV(cmPos, Pos(cell));
	}
	SETV(Pos(cell), cmPos);
}

void printTreeRecc(cellptr node, int level);

void printTree(cellptr root)
{
	printTreeRecc(root, 0);
}

void printTreeRecc(cellptr cell, int level)
{
	int i, l;
	nodeptr q;
	for (i = 0; i < NSUB; i++) {
		if ((q = Child(cell)[i]) != NULL) {
			if (Type(q) == BODY) {
				for (l = 1; l < level; l++)
					printf(" ");
				printf("%d B ", findIndex((bodyptr) q, cell));
				printBody((bodyptr) q);
				printf("\n");
			} else {
				for (l = 1; l < level; l++)
					printf(" ");
				printf("%d C ", findIndex((bodyptr) q, cell));

				printCell((cellptr) q);
				printf("\n");
				printTreeRecc((cellptr) q, level + 1);
			}
		}
	}
}

void printCell(cellptr cell)
{
	printf("[X: %lf %lf %lf][M: %lf][V: %lf %lf %lf]",
		Pos(cell)[0],
		Pos(cell)[1],
		Pos(cell)[2],
		Mass(cell),
		Vel(cell)[0],
		Vel(cell)[1],
		Vel(cell)[2]
		);
}

void printBody(bodyptr body)
{
	printf("[X: %lf %lf %lf][M: %lf][V: %lf %lf %lf]",
		Pos(body)[0],
		Pos(body)[1],
		Pos(body)[2],
		Mass(body),
		Vel(body)[0],
		Vel(body)[1],
		Vel(body)[2]
		);
}