#ifndef RIBSTRUCT_H
#define RIBSTRUCT_H

#include <unit.h>

// Структура содержит юнит,
// предполагаемое расстояние до пункта назначения по X и Y,
// орбиту и зону приземления
struct ribStruct{
    unit oneUnit;
    double diff_X;
    double diff_Y;
    int orbit;
    int area;
};

#endif // RIBSTRUCT_H
