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

params p;

void readInputFile(char * inputFile, particle * particles, int * count);

/*
 * 
 */
int main(int argc, char** argv)
{
    parseOptions(argc, argv, &p);
    printf("%.5lf, %.5lf\n", p.timeDiff, p.eps);
    particle * particles;
    int count;
    readInputFile(p.inputPath, particles, &count);
    return(EXIT_SUCCESS);
}

/**
 * Read input from file. If there is no inputFile then read from stdout
 * @param inputFile
 * @param particles
 * @param count
 */
void readInputFile(char * inputFile, particle * particles, int * count)
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
    particles = NULL;
    particle * more_particle;
    int c = 0;
    while (fscanf(fp, "%lf %lf %lf %lf", &x, &y, &z, &m) != EOF) {
        c++;
        more_particle = (int*) realloc(particles, c * sizeof(particle));
        particle p;
        p.x = x;
        p.y = y;
        p.z = z;
        p.vx = 0.0;
        p.vy = 0.0;
        p.vz = 0.0;
        p.m = m;
        if (more_particle != NULL) {
            particles = more_particle;
            particles[c - 1] = p;
        } else {
            free(particles);
            puts("Error (re)allocating memory");
            exit(EXIT_FAILURE);
        }
        printf("%d. %.5f, %.5f, %.5f, %.5f\n", c, p.x, p.y, p.z, p.m);
    }
    *count = c;
}
