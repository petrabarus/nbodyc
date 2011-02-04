/* 
 * File:   tree.h
 * Author: petra
 *
 * Created on 04 Februari 2011, 8:20
 */

#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif

    /* Node definition */
    typedef struct _node {
        short type;
        unsigned int update;
        node * next;
        
    } node;

    /* Body definition */

    typedef struct _body {
    } body;

    /* Cell definition */

    typedef struct _cell {
    } cell;

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

