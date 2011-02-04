/* 
 * File:   barneshut.h
 * Author: petra
 *
 * Created on 01 Februari 2011, 14:36
 * Driver for Barnes Hut hierarchical force-calculation algorithm
 * http://www.nature.com/nature/journal/v324/n6096/abs/324446a0.html
 */

#ifndef BARNESHUT_H
#define	BARNESHUT_H

#include "../../particle.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     *
     * @param particles
     * @param count
     * @param n
     * @param timeDiff
     * @param eps
     * @param outputPath
     */
    void nbodyBarnesHut(particle * particles,
            int count,
            int n,
            double timeDiff,
            double eps,
            char * outputPath);


#ifdef	__cplusplus
}
#endif

#endif	/* BARNESHUT_H */

