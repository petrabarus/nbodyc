/* 
 * File:   util.h
 * Author: petra
 *
 * Created on 04 Februari 2011, 13:51
 */

#ifndef UTIL_H
#define	UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif
#define ABS(x)   (((x)<0)?-(x):(x))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
        void die(char * fmt, ...);

        void eprintf(char * fmt, ...);

#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_H */

