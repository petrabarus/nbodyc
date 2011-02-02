/* 
 * File:   vtk.h
 * Author: petra
 *
 * Created on 01 Februari 2011, 15:14
 */

#ifndef VTK_H
#define	VTK_H

#include "../../particle.h"
#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * 
     * @param particles
     * @param count
     * @param filename
     */
    void vtkWriteStructuredGrid(
            char * filename,
            particle * particles,
            int count);

#ifdef	__cplusplus
}
#endif

#endif	/* VTK_H */

