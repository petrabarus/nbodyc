/* 
 * File:   randomize.c
 * Author: petra
 *
 * Created on 02 Februari 2011, 10:17
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <math.h>
#include "utils/drand48.h"

#define MULT 1103515245
#define ADD 12345
#define MASK 0x7FFFFFFF
#define TWOTO31 2147483648.0
#define PI 3.1415

char * filename;
long count;
double xmin = -1;
double xmax = 1;
double ymin = -1;
double ymax = 1;
double zmin = -1;
double zmax = 1;
double mmin = 0;
double mmax = 1;
FILE * fp;

static int A = 1;
static int B = 0;
static int randx = 1;
static int lastrand;

static void drndset(int seed)
{
	A = 1;
	B = 0;
	randx = (A * seed + B) & MASK;
	A = (MULT * A) & MASK;
	B = (MULT * B + ADD) & MASK;
}

static double drnd()
{
	lastrand = randx;
	randx = (A * randx + B) & MASK;
	return(double) lastrand / TWOTO31;
}

void parseOption(int argc, char** argv);

void random1();

void random2();

void sphere();

void sphere2();

/*
 * 
 */
int main(int argc, char** argv)
{
	/* Parse options */
	parseOption(argc, argv);
	/* Print to file */
	printf("output : %s\n", filename);
	printf("count  : %d\n", count);
	printf("xmin   : %lf\n", xmin);
	printf("ymin   : %lf\n", ymin);
	printf("zmin   : %lf\n", zmin);
	printf("mmin   : %lf\n", mmin);
	printf("xmax   : %lf\n", xmax);
	printf("ymax   : %lf\n", ymax);
	printf("zmax   : %lf\n", zmax);
	printf("mmax   : %lf\n", mmax);

	//random1();
	//sphere();
	sphere2();

	return(EXIT_SUCCESS);
}

void random1()
{
	drndset(time(NULL));
	fp = fopen(filename, "w");
	if (fp == NULL) exit(EXIT_FAILURE);
	puts("Generating");
	float rsc = (3 * PI) / 16;
	int i;
	float m, x, y, z;
	float sq;
	for (i = 0; i < count; i++) {
		printf("%d\n", i);
		//m = drnd()*1.0;
		m = 1.0 / count;
		float r = 1.0 / sqrt(pow(drnd()*0.999, -2.0 / 3.0) - 1);
		do {
			x = drnd()*2.0 - 1.0;
			y = drnd()*2.0 - 1.0;
			z = drnd()*2.0 - 1.0;
			sq = x * x + y * y + z * z;
		} while (sq > 1.0);
		float scale = rsc * r / sqrt(sq);
		x = x * scale;
		x = y * scale;
		x = z * scale;
		fprintf(fp, "%lf %lf %lf %lf\n", x, y, z, m);
	}
	fclose(fp);
}

void random2()
{
	double m, x, y, z;
	srand(time(NULL));
	fp = fopen(filename, "w");
	if (fp == NULL) exit(EXIT_FAILURE);
	puts("Generating");
	int i;

	for (i = 0; i < count; i++) {
		printf("%d\n", i);
		x = ((rand() / (double) RAND_MAX) * (xmax - xmin)) + xmin;
		y = ((rand() / (double) RAND_MAX) * (ymax - ymin)) + ymin;
		z = ((rand() / (double) RAND_MAX) * (zmax - zmin)) + zmin;
		m = ((rand() / (double) RAND_MAX) * (mmax - mmin)) + mmin;
		fprintf(fp, "%lf %lf %lf %lf\n", x, y, z, m);
	}

	fclose(fp);
}

void sphere2()
{
	srand(time(NULL));
	int i;
	double x, y, z, w, t;
	double m = 1.0 / count;
	fp = fopen(filename, "w");
	srand48(time(NULL));
	if (fp == NULL) exit(EXIT_FAILURE);
	int coord[4][3] = {
		{5, 5, 0},
		{5, -5, 0},
		{-5, 5, 0},
		{-5, -5, 0},
	};
	int j;
	for (j = 0; j < 4; j++) {
		for (i = 0; i < count; i++) {
			printf("%d\n", i);
			z = 2.0 * drand48() - 1.0 + coord[j][2];
			t = 2.0 * M_PI * drand48();
			w = sqrt(1 - z * z);
			x = w * cos(t) + coord[j][0];
			y = w * sin(t) + coord[j][1];
			fprintf(fp, "%lf %lf %lf %lf\n", x, y, z, m);
		}
	}
	fclose(fp);
}

void sphere()
{
	srand(time(NULL));
	int i;
	double x, y, z, w, t;
	double m = 1.0 / count;
	fp = fopen(filename, "w");
	srand48(time(NULL));
	if (fp == NULL) exit(EXIT_FAILURE);
	for (i = 0; i < count; i++) {
		printf("%d\n", i);
		z = 2.0 * drand48() - 1.0;
		t = 2.0 * M_PI * drand48();
		w = sqrt(1 - z * z);
		x = w * cos(t);
		y = w * sin(t);
		fprintf(fp, "%lf %lf %lf %lf\n", x, y, z, m);
	}
	fclose(fp);
}

void parseOption(int argc, char** argv)
{
	int c;
	static const char *optstring = "n:x:y:z:m:X:Y:Z:M:o:";
	static struct option long_options[] = {
		{"count", required_argument, NULL, 'n'},
		{"xmin", required_argument, NULL, 'x'},
		{"xmax", required_argument, NULL, 'X'},
		{"ymin", required_argument, NULL, 'y'},
		{"ymax", required_argument, NULL, 'Y'},
		{"zmin", required_argument, NULL, 'z'},
		{"zmax", required_argument, NULL, 'Z'},
		{"mmin", required_argument, NULL, 'm'},
		{"mmax", required_argument, NULL, 'M'},
		{"output", required_argument, NULL, 'o'},
	};
	while ((c = getopt_long(argc, argv, optstring, long_options, NULL)) != -1) {
		switch (c) {
		case 'n':
			count = atoi(optarg);
			break;
		case 'x':
			xmin = atof(optarg);
			break;
		case 'X':
			xmax = atof(optarg);
			break;
		case 'y':
			ymin = atof(optarg);
			break;
		case 'Y':
			ymax = atof(optarg);
			break;
		case 'z':
			zmin = atof(optarg);
			break;
		case 'Z':
			zmax = atof(optarg);
			break;
		case 'm':
			mmin = atof(optarg);
			break;
		case 'M':
			mmax = atof(optarg);
			break;
		case 'o':
			filename = optarg;
			break;
		}
	}
}