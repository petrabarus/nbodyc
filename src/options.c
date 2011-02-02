/*
 * File:   options.c
 * Author: petra
 *
 * Created on 31 Januari 2011, 14:28
 */
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#include "options.h"

/**
 * Initiate the parameters
 * @param p
 */
void initiateParams(params *p);

/**
 * Parsing the application argument
 * @param argc Argument count
 * @param argv Argument values
 * @param p Application param
 */
void parseOptions(int argc, char ** argv, params * p)
{
	int c;
	static const char *optstring = "-hvt:e:i:o:n:";
	static struct option long_options[] = {
		{"timediff", required_argument, NULL, 't'},
		{"epsilon", required_argument, NULL, 'e'},
		{"input", required_argument, NULL, 'i'},
		{"iteration", required_argument, NULL, 'n'},
		{"output", required_argument, NULL, 'o'},
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'v'},
	};
	initiateParams(p);
	while ((c = getopt_long(argc, argv, optstring, long_options, NULL)) != -1) {
		switch (c) {
		case 't':
			p->timeDiff = atof(optarg);
			break;
		case 'e':
			p->eps = atof(optarg);
			break;
		case 'i':
			p->inputPath = optarg;
			break;
		case 'o':
			p->outputPath = optarg;
			break;
		case 'n':
			p->n = atoi(optarg);
			break;
		case 'h':
			exit(EXIT_SUCCESS);
		case 'v':
			exit(EXIT_SUCCESS);
		}
	}
}

void initiateParams(params* p)
{
	p->timeDiff = DEFAULT_TIME_DIFFERENCE;
	p->eps = DEFAULT_EPSILON;
	p->inputPath = NULL;
	p->outputPath = NULL;
}