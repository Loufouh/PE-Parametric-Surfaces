//
// Created by Louis Masson on 10/10/2022.
//

#include "surface_bernstein.h"
#include "../parametric_curves/berstein.h"

std::vector<std::vector<Vec3> > BezierSurfaceByBernstein(
        std::vector<std::vector<Vec3> > &gridControlPoints,
        long nbControlPointsU,
        long nbControlPointsV,
        long nbU,
        long nbV
) {
    std::vector<std::vector<Vec3> > surfacePoints;

    surfacePoints.reserve(nbU + nbV);

    for (long i = 0; i < nbU; i++) {
        float u = (float) i / ((float) nbU - 1);

        surfacePoints.push_back({});
        surfacePoints.back().reserve(nbV);

        for (long j = 0; j < nbV; j++) {
            float v = (float) j / ((float) nbV - 1);

            surfacePoints.back().push_back(
                    BezierSurfacePointByBernstein(
                            gridControlPoints,
                            nbControlPointsU,
                            nbControlPointsV,
                            u,
                            v
                    )
            );
        }
    }

    // Ajouter les iso-lignes "verticales"
    for(int j = 0; j < nbV; j++) {
        surfacePoints.push_back({});
        surfacePoints.back().reserve(nbU);

        for(int i = 0; i < nbU; i++) {
            surfacePoints.back().push_back(
                    surfacePoints[i][j]
            );
        }
    }

    return surfacePoints;
}

Vec3 BezierSurfacePointByBernstein(
        const std::vector<std::vector<Vec3> > &gridControlPoints,
        long nbControlPointsU,
        long nbControlPointsV,
        float u,
        float v
) {
    Vec3 point = Vec3(0, 0, 0);

    for (int i = 0; i < gridControlPoints.size(); i++) {
        float Bi = BernsteinPoly(nbControlPointsU - 1, i, u);

        for (int j = 0; j < gridControlPoints.size(); j++) {
            float Bj = BernsteinPoly(nbControlPointsV - 1, j, v);

            point += Bi * Bj * gridControlPoints[i][j];
        }
    }

    return point;
}
