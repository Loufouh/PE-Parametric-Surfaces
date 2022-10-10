//
// Created by Louis Masson on 04/10/2022.
//

#include "surface_cylindrique.h"
#include "../parametric_curves/casteljau.h"

std::vector< std::vector<Vec3> > surfaceCylindrique(
        const std::vector<Vec3> &bezierControlPoints,
        const std::vector<Vec3> linePoints,
        unsigned int nbU,
        unsigned int nbV
) {
    Vec3 lineVec = linePoints[1] - linePoints[0];
    lineVec.normalize();

    std::vector< std::vector<Vec3> > surfacePoints;
    surfacePoints.reserve(nbU);

    for(unsigned int x = 0; x < nbU; x++) {
        float u = (float) x / (float) (nbU - 1);

        surfacePoints.push_back({});
        surfacePoints.back().reserve(nbV);

        for(unsigned int y = 0; y < nbV; y++) {
            float v = (float) y / (float) (nbV - 1);

            Vec3 translationVec = v*lineVec;
            Vec3 bezierPoint = BezierPointByCasteljau(bezierControlPoints, u);

            surfacePoints[x][y] = translationVec + bezierPoint;
        }
    }

    std::vector< std::vector<Vec3> > isoCurves;
    isoCurves.reserve(nbU + nbV);

    std::vector<Vec3> curve;

    for(unsigned int x = 0; x < nbU; x++) {
        curve.clear();
        curve.reserve(nbV);

        for(unsigned int y = 0; y < nbV; y++) {
            curve.push_back(surfacePoints[x][y]);
        }

        isoCurves.push_back(curve);
    }

    for(unsigned int y = 0; y < nbV; y++) {
        curve.clear();
        curve.reserve(nbU);

        for(unsigned int x = 0; x < nbU; x++) {
            curve.push_back(surfacePoints[x][y]);
        }

        isoCurves.push_back(curve);
    }

    return isoCurves;
}
