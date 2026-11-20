/*
Given two points in 3D Cartesian coordinates,
find the Euclidean distance between the points.
*/

#include <basicgol.h>

// We use a struct to organize data belonging to a point
REGISTRO(Point3D)
    REAL x;
    REAL y;
    REAL z;
FIM_REGISTRO(Point3D);

FUNCAO REAL euclidean_dist(Point3D a, Point3D b) {
    RETORNE RAIZ(POTENCIA(a.x - b.x, 2) + POTENCIA(a.y - b.y, 2) + POTENCIA(a.z - b.z, 2));
}

INICIO
    Point3D a = { 5.5, 8, 9 };
    Point3D b = { 3, 5, 4.3 };

    ESCREVA_FMT("Distance is %g", euclidean_dist(a, b));

    RETORNE 0;
FIM
