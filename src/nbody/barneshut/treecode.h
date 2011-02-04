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
#define NSUB (1 << NDIM)

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
            nodeptr child[NSUB];
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
     */
    void treeInit(cellptr * root, bodyptr bodies, int nbody);

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
    void treeInsert(cellptr * root, bodyptr body);
#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

