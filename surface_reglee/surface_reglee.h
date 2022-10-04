//
// Created by Louis Masson on 04/10/2022.
//

#ifndef MODELISATION_TP1_SURFACE_REGLEE_H
#define MODELISATION_TP1_SURFACE_REGLEE_H

#include <vector>
#include "../src/Vec3.h"

extern std::vector<std::vector<Vec3> > surfaceReglee(
        const std::vector<Vec3> &bezierControlPoints1,
        const std::vector<Vec3> &bezierControlPoints2,
        unsigned int nbU,
        unsigned int nbV
);

#endif //MODELISATION_TP1_SURFACE_REGLEE_H
