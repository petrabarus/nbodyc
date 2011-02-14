/* 
 * File:   treecode.h
 * Author: petra
 *
 * Created on 04 Februari 2011, 8:20
 * Based on Joshue E. Barnes
 * http://www.ifa.hawaii.edu/~barnes/treecode/
 */

#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif
        /* Dimension 3 */
#define NDIM 3
        typedef float real;
        typedef float *realptr;
        typedef real vector[NDIM];
        typedef real matrix[NDIM][NDIM];
        /* Vector Operations */
        /* Clear vector */
#define CLRV(v)				                   		\
{									\
    int _i;								\
    for (_i = 0; _i < NDIM; _i++)					\
        (v)[_i] = 0.0;							\
}

        /* Set Vector */
#define SETV(v,u)				                 	\
{ 									\
    int _i; 								\
    for (_i = 0; _i < NDIM; _i++) 					\
        (v)[_i] = (u)[_i]; 						\
}
        /* MUL Vect by Scalar, ADD to vect */
#define ADDMULVS(v,u,s)                                                 \
{                                                                       \
    (v)[0] += (u)[0] * (s);                                             \
    (v)[1] += (u)[1] * (s);                                             \
    (v)[2] += (u)[2] * (s);                                             \
}
        /* MULtiply Vector by Scalar */
#define MULVS(v,u,s)		                        		\
{									\
    (v)[0] = (u)[0] * (s);						\
    (v)[1] = (u)[1] * (s);						\
    (v)[2] = (u)[2] * (s);						\
}

        /* DIVide Vector by Scalar */
#define DIVVS(v,u,s)		                         		\
{									\
    (v)[0] = (u)[0] / (s);						\
    (v)[1] = (u)[1] / (s);						\
    (v)[2] = (u)[2] / (s);						\
}
#define SETM(p,q)		/* SET Matrix */			\
{									\
    int _i, _j;								\
    for (_i = 0; _i < NDIM; _i++)					\
        for (_j = 0; _j < NDIM; _j++)					\
	    (p)[_i][_j] = (q)[_i][_j];					\
}

        /* Node definition */

        typedef struct _node {
                /* Node type */
                short type;
                /* Force calculation status */
                unsigned int update;
                /* Link to next force calculation */
                struct _node * next;
                /* Mass */
                real mass;
                /* Position */
                vector pos;
        } node;

        typedef node * nodeptr;

#define BODY 1                 /* type code for bodies */
#define CELL 2                 /* type code for cells */

#define Type(x)   (((nodeptr) (x))->type)
#define Update(x) (((nodeptr) (x))->update)
#define Next(x)   (((nodeptr) (x))->next)
#define Mass(x)   (((nodeptr) (x))->mass)
#define Pos(x)    (((nodeptr) (x))->pos)

        /* Body definition */


        typedef struct _body {
                /* Data common to all nodes */
                node bodynode;
                /* Velocity */
                vector v;
                /* Acceleration */
                vector a;
                /* Potential at body */
                real phi;
        } body;

        typedef body * bodyptr;

#define Vel(x)    (((bodyptr) (x))->v)
#define Acc(x)    (((bodyptr) (x))->a)
#define Phi(x)    (((bodyptr) (x))->phi)

        /* Cell definition */
#define NCHILD (1 << NDIM)

        typedef struct _cell {
                /* Data common to all nodes */
                node cellnode;

                union {
                        /* Link to first descendent */
                        nodeptr more;
                        /* Dist from last force sum */
                        real dlast;
                } mord;

                union {
                        /* Descendents of cell */
                        nodeptr child[NCHILD];
                        /* Quad. moment of cell */
                        matrix quad;
                } sorq;
        } cell;

        typedef cell * cellptr;

#define More(x)   (((cellptr) (x))->mord.more)
#define Dlast(x)  (((cellptr) (x))->mord.dlast)
#define Child(x)   (((cellptr) (x))->sorq.child)
#define Quad(x)   (((cellptr) (x))->sorq.quad)


        /* */

        /**
         * Initialize tree structure for hierarchical force calculation
         * @param root Root of the tree to be initiated
         * @param bodies Array of bodies to be calculate
         * @param nbody The number of bodies
         * @param rootSize The size of the root produced
         */
        void treeInit(cellptr * root, bodyptr bodies, int nbody, real * rootSize);

        /**
         * Free an existing tree claiming back the memory used.
         * @param root Tree to be freed
         */
        void treeFree(cellptr * root);

        /**
         * Insert body into tree
         * @param root Root of the tree to be initiated
         * @param body The body to be inserted
         */
        void treeInsert(cellptr * root, real rsize, bodyptr body);

        /**
         * Create a new fre cell
         * @return Pointer to free cell
         */
        cellptr treeCreateCell();

        /**
         * Find tree depth
         * @param root
         * @return
         */
        int treeDepth(cellptr root);

        /**
         * 
         * @param root
         */
        void printTree(cellptr root);

        /**
         * 
         * @param body
         */
        void printBody(bodyptr body);

        /**
         *
         * @param cell
         */
        void printCell(cellptr cell);


        void calculateForce(cellptr root, double eps, real rootSize);


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
         * Recursively calculating center of mass for a cell
         * @param cell Cell to be calculated
         */
        void calculateCenterOfMass(cellptr cell);

        void printTreeRec(cellptr node, int level);

        int treeDepthRec(cellptr node);

        /**
         * Walk a tree to calculate force iteratively
         * @param aPtr Active list first element
         * @param nPtr Active list second element
         * @param cPtr Interaction list first element
         * @param bPtr Interaction list last element
         * @param p Tree root
         * @param pSize Tree size
         * @param pMid Tree middle point
         * @param eps Epsilon
         */
        void walkTree(nodeptr * aPtr, nodeptr *nPtr,
                cellptr cPtr, cellptr bPtr,
                nodeptr p, real pSize, vector pMid, double eps);

        /**
         *
         * @param node
         * @param pSize
         * @param pMid
         * @return
         */
        bool acceptNode(nodeptr node, real pSize, vector pMid);

        /**
         * Do a recursive tree walk to install Next and More link
         * @param start Starting node
         * @param stop Stopping node
         */
        void makeThread(nodeptr start, nodeptr end);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

