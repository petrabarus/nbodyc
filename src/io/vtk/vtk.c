/*
 * File:   vtk.c
 * Author: petra
 *
 * Created on 01 Februari 2011, 15:14
 */

#include <stdio.h>
#include "vtk.h"

void vtkWriteStructuredGrid(
		char * filename,
		particle * particles,
		int count)
{
	FILE *out;
	puts(filename);
	out = fopen(filename, "w");
	fprintf(out, "# vtk DataFile Version 3.0\n");
	fprintf(out, "Generated from http://github.com/petrabarus/nbodyc\n");
	fprintf(out, "ASCII\n");
	fprintf(out, "DATASET POLYDATA\n");
	//fprintf(out, "DIMENSIONS %d %d %d\n", count, count, count);
	fprintf(out, "POINTS %d double"
			"\n", count);
	int i;
	for (i = 0; i < count; i++) {
		fprintf(out, "%lf %lf %lf\n", particles[i].x, particles[i].y, particles[i].z);
	}

	fprintf(out, "VERTICES %d %d\n", count, count * 2);
	for (i = 0; i < count; i++) {
		fprintf(out, "%d %d\n", 1, i);
	}
	fclose(out);
}