/* 
 * File:   params.h
 * Author: petra
 *
 * Created on 01 Februari 2011, 11:11
 */

#ifndef PARAMS_H
#define	PARAMS_H

#ifdef	__cplusplus
extern "C" {
#endif
#define DEFAULT_TIME_DIFFERENCE 0.00001
#define DEFAULT_EPSILON 0.0001

    /**
     * Application parameter
     */
    typedef struct params {
        /* Time difference between each n-body state */
        double timeDiff;
        /* Epsilon */
        double eps;
        /**/
        char * inputPath;
        char * outputPath;
    } params;

#ifdef	__cplusplus
}
#endif

#endif	/* PARAMS_H */

