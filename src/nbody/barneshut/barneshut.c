/*
 * File:   barneshut.c
 * Author: petra
 *
 * Created on 01 Februari 2011, 12:47
 * Driver for Barnes Hut hierarchical force-calculation algorithm
 * http://www.nature.com/nature/journal/v324/n6096/abs/324446a0.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "barneshut.h"
#include "treecode.h"
#include "../../io/vtk/vtk.h"

char fileParamBuff[255];

/**
 * Convert the particles from particle structure into body structure
 * @param particles Particles to be converted
 * @param count Number of bodies
 * @return Bodies
 */
bodyptr convertStruct(particle * particles, int count);

void nbodyBarnesHut(particle * particles,
		int count,
		int n,
		double timeDiff,
		double eps,
		char * outputPath)
{
	int step;
	sprintf(fileParamBuff, "%s_%%0%dd.vtk", outputPath, ((int) log10(n) + 1));
	bodyptr bodies = convertStruct(particles, count);
	/* End converting */
	/* Do the stepping */
	bodyptr p;
	for (step = 1; step <= n; step++) {
		//make the tree
		//summarize body
		//compute force
		//Advance each body
		for (p = bodies; p < bodies + count; p++){
			//Advance the speed
			//Advance the position
		}
	}
}

bodyptr convertStruct(particle* particles, int count)
{
	bodyptr bodies = (bodyptr) malloc(count * sizeof(body));
	bodyptr body = bodies;
	particle * p;
	for (p = particles; p < particles + count; p++) {
		Pos(body)[0] = p->x;
		Pos(body)[1] = p->y;
		Pos(body)[2] = p->z;
		Mass(body) = p->m;
		Vel(body)[0] = p->vx;
		Vel(body)[1] = p->vy;
		Vel(body)[2] = p->vz;
		body++;
	}
	return bodies;
}