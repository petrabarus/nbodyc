/*
 * File:   main.c
 * Author: petra
 *
 * Created on 31 Januari 2011, 14:25
 */

#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "options.h"
#include "particle.h"
#include "nbody/direct/direct.h"
#include "nbody/barneshut/barneshut.h"

params appParams;

/**
 * Read input from file. If there is no inputFile then read from stdout
 * @param inputFile
 * @param particles
 * @param count
 */
void readInputFile(char * inputFile, particle * * particles, int * count);

/**
 * Main program
 */
int main(int argc, char** argv)
{
	parseOptions(argc, argv, &appParams);
	particle * particles;
	int count;
	readInputFile(appParams.inputPath, &particles, &count);
	//nbodyDirect(particles, count, appParams.n,
	//		appParams.timeDiff, appParams.eps, appParams.outputPath);
	nbodyBarnesHut(particles, count, appParams.n,
			appParams.timeDiff, appParams.eps, appParams.outputPath);
	return(EXIT_SUCCESS);
}

void readInputFile(char * inputFile, particle * * particles, int * count)
{
	FILE * fp;
	//If there is input file then read from stdout
	if (inputFile != NULL) {
		fp = fopen(inputFile, "r");
	} else
		fp = stdout;
	//Exit if file not found
	if (fp == NULL)
		exit(EXIT_FAILURE);
	//Do reading
	double x, y, z, m;
	(*particles) = NULL;
	particle * more_particles;
	int c = 0;
	while (fscanf(fp, "%lf %lf %lf %lf", &x, &y, &z, &m) != EOF) {
		c++;
		more_particles = (particle*) realloc((*particles), c * sizeof(particle));
		particle p;
		p.x = x;
		p.y = y;
		p.z = z;
		p.vx = 0.0;
		p.vy = 0.0;
		p.vz = 0.0;
		p.m = m;
		if (more_particles != NULL) {
			(*particles) = more_particles;
			(*particles)[c - 1] = p;
		} else {
			free(particles);
			puts("Error (re)allocating memory");
			exit(EXIT_FAILURE);
		}
	}
	(*count) = c;

}
