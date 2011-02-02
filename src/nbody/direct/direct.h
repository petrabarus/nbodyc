/* 
 * File:   direct.h
 * Author: petra
 *
 * Created on 01 Februari 2011, 14:24
 */

#ifndef DIRECT_H
#define	DIRECT_H

#include "../../particle.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Simulate the N-Body using direct computation
     * @param particles Array of particles
     * @param count Particles count
     * @param n Number of iteratin
     * @param timeDiff Time difference for each iteration
     * @param eps Epsilon
     * @param outputPath Output folder
     */
    void nbodyDirect(
            particle * particles,
            int count,
            int n,
            double timeDiff,
            double eps,
            char * outputPath);

#ifdef	__cplusplus
}
#endif

#endif	/* DIRECT_H */

