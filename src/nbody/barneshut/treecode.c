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

void treeInit(cellptr * root, bodyptr bodies, int nbody)
{
        bodyptr p;
        real rootSize = 1.0;
        /* Count the root size */
        rootSize = expandBox(*root, rootSize, bodies, nbody);
        (*root) = treeCreateCell();
        /* Foreach bodies */
        int i = 0;
        for (p = bodies; p < bodies + nbody; p++)
                /* Insert into tree */
                treeInsert(root, rootSize, p);
}

void treeFree(cellptr * root)
{
        nodeptr p;
        if (root != NULL) {
                /* Start with the root */
                p = (nodeptr) root;
                while (p != NULL) {
                        if (Type(p) == CELL) {

                        }
                }
        }
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