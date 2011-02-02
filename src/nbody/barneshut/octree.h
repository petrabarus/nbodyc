/* 
 * File:   octree.h
 * Author: petra
 *
 * Created on 02 Februari 2011, 12:47
 */

#ifndef OCTREE_H
#define	OCTREE_H

#define MAX3(a,b,c) ( ((a)>(b)) ? max((a),(c)) : max((b),(c)) )

typedef struct octreeNodeStruct OCTREE_NODE;

struct octreeNodeStruct {
    /* Child octree */
    OCTREE_NODE * child[8];
};

/**/


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* OCTREE_H */

