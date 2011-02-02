/*
 * File:   direct.c
 * Author: petra
 *
 * Created on 01 Februari 2011, 14:24
 */

#include <stdio.h>
#include <math.h>
#include "direct.h"
#include "../../io/vtk/vtk.h"

char fileParamBuff[255];

/**
 * 
 * @param outputPath
 * @param particles
 * @param count
 */
void nbodyDirectPrintParticles(
		char * outputPath,
		particle * particles,
		int count);

void nbodyDirect(
		particle * particles,
		int count,
		int n,
		double timeDiff,
		double eps,
		char * outputPath)
{
	sprintf(fileParamBuff, "%s_%%0%dd.vtk", outputPath, ((int) log10(n) + 1));

	/**/
	double dx, dy, dz; /* position differences */
	double ax, ay, az; /* acceleration */
	double xnew[count];
	double ynew[count];
	double znew[count];
	int i;
	int j;
	int state = 0;
	char filename[255];
	sprintf(filename, fileParamBuff, state);
	nbodyDirectPrintParticles(filename, particles, count);
	for (state = 1; state <= n; state++) {
		for (i = 0; i < count; i++) {
			ax = 0.0;
			ay = 0.0;
			az = 0.0;
			for (j = 0; j < count; j++) {
				dx = particles[j].x - particles[i].x;
				dy = particles[j].y - particles[i].y;
				dz = particles[j].z - particles[i].z;
				double invr = 1.0 / sqrt(dx * dx + dy * dy + dz * dz + eps);
				double invr3 = invr * invr * invr;
				double f = particles[j].m * invr3; /* ??? */
				/* accumulating force */
				ax += f * dx;
				ay += f * dy;
				az += f * dz;
			}
			/* storing the new x position */
			xnew[i] = particles[i].x + timeDiff * particles[i].vx + 0.5 * timeDiff * timeDiff * ax;
			ynew[i] = particles[i].y + timeDiff * particles[i].vy + 0.5 * timeDiff * timeDiff * ay;
			znew[i] = particles[i].z + timeDiff * particles[i].vz + 0.5 * timeDiff * timeDiff * az;
			/* updating velocity */
			particles[i].vx += timeDiff * ax;
			particles[i].vy += timeDiff * ax;
			particles[i].vz += timeDiff * ax;
		}
		for (i = 0; i < count; i++) {
			particles[i].x = xnew[i];
			particles[i].y = ynew[i];
			particles[i].z = znew[i];
		}
		/* print the state */
		
		sprintf(filename, fileParamBuff, state);
		nbodyDirectPrintParticles(filename, particles, count);
	}
}

void nbodyDirectPrintParticles(
		char * outputPath,
		particle * particles,
		int count)
{

	vtkWriteStructuredGrid(outputPath, particles, count);
}