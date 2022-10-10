//
// Created by Louis Masson on 10/10/2022.
//

#ifndef MODELISATION3D_TP4_SURFACE_BERNSTEIN_H
#define MODELISATION3D_TP4_SURFACE_BERNSTEIN_H

#include <vector>
#include "../src/Vec3.h"

extern std::vector< std::vector<Vec3> > BezierSurfaceByBernstein(
        std::vector< std::vector<Vec3> > &gridControlPoints,
        long nbControlPointsU,
        long nbControlPointsV,
        long nbU,
        long nbV
);

extern Vec3 BezierSurfacePointByBernstein(
        const std::vector< std::vector<Vec3> > &gridControlPoints,
        long nbControlPointsU,
        long nbControlPointsV,
        float u,
        float v
);

#endif //MODELISATION3D_TP4_SURFACE_BERNSTEIN_H
