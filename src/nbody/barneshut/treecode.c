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
#include "../../utils/util.h"

void treeInit(cellptr * root, bodyptr bodies, int nbody, real * rootSize)
{
	bodyptr p;
	(*rootSize) = 1.0;
	/* Count the root size */
	(*rootSize) = expandBox(*root, *rootSize, bodies, nbody);
	(*root) = treeCreateCell();
	/* Foreach bodies */
	int i = 0;
	for (p = bodies; p < bodies + nbody; p++) {
		/* Insert into tree */
		treeInsert(root, *rootSize, p);
	}
	calculateCenterOfMass(*root);
	makeThread((nodeptr) * root, NULL);
}

void treeFree(cellptr * cell)
{
	int i;

	nodeptr q;
	for (i = 0; i < NCHILD; i++) {
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
	for (i = 0; i < NCHILD; i++) {
		Child(c)[i] = NULL;
	}
	return c;
}

int treeDepth(cellptr root)
{
	return treeDepthRec(root);
}

int treeDepthRec(cellptr node)
{
	int i, l = 0;
	nodeptr q;
	for (i = 0; i < NCHILD; i++) {
		if ((q = Child(node)[i]) != NULL)
			/* If node is a cell */
			if (Type(q) == BODY) {
				l = MAX(l, 0);
			} else {
				l = MAX(l, 1 + treeDepth((cellptr) q));
			}
	}
	return l;
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
			idx += NCHILD >> (k + 1);
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
	for (i = 0; i < NCHILD; i++) {
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

void printTree(cellptr root)
{
	printTreeRec(root, 0);
}

void printTreeRec(cellptr cell, int level)
{
	int i, l;
	nodeptr q;
	for (i = 0; i < NCHILD; i++) {
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
				printTreeRec((cellptr) q, level + 1);
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

void calculateForce(cellptr root, double eps, real rootSize)
{
	/* List of nodes to be calculate */
	nodeptr * activeList;
	/* List of interacting nodes */
	cellptr interactionList;
	/* Maximum number of active nodes */
	int activeMaxCount;
	/* Center of root */
	vector rMid;
	/* */
	/* Estimate list length     */
	activeMaxCount = 216 * (treeDepth(root) + 1);

	activeList = (nodeptr*) malloc(activeMaxCount * sizeof(nodeptr));
	interactionList = (cellptr) malloc(activeMaxCount * sizeof(cell));

	/* Initialize active list */
	activeList[0] = (nodeptr) root;
	/* Initialize center of root */
	CLRV(rMid)
	/* Start walking the tree */
	walkTree(activeList, activeList + 1,
		interactionList, interactionList + activeMaxCount,
		(nodeptr) root, rootSize, rMid,
		eps);
	/* Cleaning up */
	free(activeList);
	free(interactionList);
}

void walkTree(nodeptr * aPtr, nodeptr *nPtr,
	cellptr cPtr, cellptr bPtr,
	nodeptr p, real pSize, vector pMid, double eps)
{
	nodeptr *np, *ap, q;
	int activeSafe;

	/* Are new forces needed? */
	if (Update(p)) {
		/* Start new active list */
		np = nPtr;
		/* Loop over active nodes   */
		for (ap = aPtr; ap < nPtr; ap++) {
			/* Is this node a cell?     */
			if (Type(*ap) == CELL) {
				/* If the node pass the test */
				if (acceptNode(*ap, pSize, pMid)) {
					/* If the node contribute to the field */
					if (Mass(*ap) > 0.0) {
						/* Copy to interaction list */
						Mass(cPtr) = Mass(*ap);
						SETV(Pos(cPtr), Pos(*ap));
						/* Next interaction element */
						cPtr++;
					}
				} else { /* If not accepted */
					for (q = More(*ap); q != Next(*ap); q = Next(q))
						*np++ = q;
				}
			} else {/* If this node is a body */
				/* If it's not self-interaction */
				if (*ap != p && Mass(*ap) > 0.0) {
					/* Build interaction element */
					--bPtr;
					/* Copy data to array */
					Mass(bptr) = Mass(*ap);
					SETV(Pos(bPtr), Pos(*ap));
				}
			}
		}
	}
}

bool acceptNode(nodeptr node, real pSize, vector pMid)
{
	real p15, dk;
	int i = 0;
	/* Premultiply cell size    */
	p15 = ((real) 1.5) * pSize;
	for (i = 0; i < NDIM; i++) {
		/* Find distance to the midpoint */
		dk = Pos(node)[i] - pMid[0];
		/* If node far enough from the midpoint  */
		if (ABS(dk) > p15)
			/* Accept interaction */
			return(TRUE);
	}
	return(FALSE);
}

void makeThread(nodeptr start, nodeptr stop)
{
	int ndesc, i;
	nodeptr desc[NCHILD + 1];
	/* Set link to the next node */
	Next(start) = stop;
	/* If could descendent to thread */
	if (Type(start) == CELL) {
		/* Start counting */
		ndesc = 0;
		/* Loop over all child cells  */
		for (i = 0; i < NCHILD; i++)
			/* If this one is occupied */
			if (Child(start)[i] != NULL)
				/* Store it in the table */
				desc[ndesc++] = Child(start)[i];
		/* Set link to the first one */
		More(start) = desc[0];
		/* Thread last one to next */
		desc[ndesc] = stop;
		/* Loop over descendents */
		for (i = 0; i < ndesc; i++)
			/* Thread them together */
			makeThread(desc[i], desc[i + 1]);
	}
}