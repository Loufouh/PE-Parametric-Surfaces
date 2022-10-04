//
// Created by Louis Masson on 04/10/2022.
//

#ifndef MODELISATION_TP1_SURFACE_CYLINDRIQUE_H
#define MODELISATION_TP1_SURFACE_CYLINDRIQUE_H

#include <vector>
#include "../src/Vec3.h"

extern std::vector< std::vector<Vec3> > surfaceCylindrique(
        const std::vector<Vec3> &bezierControlPoints,
        const std::vector<Vec3> linePoints,
        unsigned int nbU,
        unsigned int nbV
);

#endif //MODELISATION_TP1_SURFACE_CYLINDRIQUE_H
