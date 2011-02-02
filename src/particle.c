/*
 * File:   particle.c
 * Author: petra
 *
 * Created on 31 Januari 2011, 14:28
 */

#include <stdio.h>
#include "particle.h"

void printParticle(FILE * fp, particle particle)
{
	fprintf(fp, "[(%lf,%lf,%lf),(%lf,%lf,%lf),%lf]",
			particle.x, particle.y, particle.z,
			particle.vx, particle.vy, particle.vz,
			particle.m);
}
