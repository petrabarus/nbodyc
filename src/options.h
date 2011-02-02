/* 
 * File:   options.h
 * Author: petra
 *
 * Created on 31 Januari 2011, 14:28
 */

#ifndef OPTIONS_H
#define	OPTIONS_H

#include "params.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Parsing the application argument
     * @param argc Argument count
     * @param argv Argument values
     * @param p Application param
     */
    void parseOptions(int argc, char ** argv, params * p);

#ifdef	__cplusplus
}
#endif

#endif	/* OPTIONS_H */

