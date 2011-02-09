/*
 * File:   util.h
 * Author: petra
 *
 * Created on 04 Februari 2011, 13:51
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "util.h"

void die(char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fflush(stderr);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void eprintf(char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap); /* invoke interface to printf       */
	fflush(stderr); /* drain std error buffer 	    */
	va_end(ap);
}