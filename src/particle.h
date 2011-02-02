/* 
 * File:   particle.h
 * Author: petra
 *
 * Created on 31 Januari 2011, 14:28
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct particle {
        /* Coordinate of the particle */
        double x;
        double y;
        double z;
        /* Velocity of the particle */
        double vx;
        double vy;
        double vz;
        /* Mass of the particle */
        double m;
    } particle;

    void printParticle(FILE * fp, particle particle);

#ifdef	__cplusplus
}
#endif

#endif	/* PARTICLE_H */

