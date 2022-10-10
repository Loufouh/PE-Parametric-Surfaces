//
// Created by Louis Masson on 04/10/2022.
//

#include "surface_reglee.h"

#include "../parametric_curves/casteljau.h"

std::vector< std::vector<Vec3> > surfaceReglee(
        const std::vector<Vec3> &bezierControlPoints1,
        const std::vector<Vec3> &bezierControlPoints2,
        unsigned int nbU,
        unsigned int nbV
) {
    std::vector< std::vector<Vec3> > surfacePoints;
    surfacePoints.reserve(nbU + 1);

    for(unsigned int x = 0; x <= nbU; x++) {
        float u = (float) x / (float) nbU;

        surfacePoints.push_back({});
        surfacePoints.back().reserve(nbV + 1);

        for(unsigned int y = 0; y <= nbV; y++) {
            float v = (float) y / (float) nbV;

            Vec3 p1 = BezierPointByCasteljau(bezierControlPoints1, u);
            Vec3 p2 = BezierPointByCasteljau(bezierControlPoints2, u);

            Vec3 vec = p2 - p1;

            surfacePoints[x][y] = p1 + v*vec;
        }
    }

    std::vector< std::vector<Vec3> > isoCurves;
    isoCurves.reserve((nbU + 1) + (nbV + 1));

    std::vector<Vec3> curve;

    for(unsigned int x = 0; x <= nbU; x++) {
        curve.clear();
        curve.reserve(nbV);

        for(unsigned int y = 0; y <= nbV; y++) {
            curve.push_back(surfacePoints[x][y]);
        }

        isoCurves.push_back(curve);
    }

    for(unsigned int y = 0; y <= nbV; y++) {
        curve.clear();
        curve.reserve(nbU);

        for(unsigned int x = 0; x <= nbU; x++) {
            curve.push_back(surfacePoints[x][y]);
        }

        isoCurves.push_back(curve);
    }

    return isoCurves;
}
