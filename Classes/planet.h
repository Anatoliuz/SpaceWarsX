#ifndef PLANET_H
#define PLANET_H

#include "sector.h"
#include <math.h>
#include <iostream>
class planet
{

public:
    planet();// Констуктор по умолчанию создает планету с координатами (0, 0)
    
    void set_dt(float);
    float get_dt();
    
    static planet* create();
    sector** getMassOfSectors();
    double get_planet_radius();
    coordinate_X_Y get_planet_coordinates();

private:
    float dt;
    
    double radiusOfPlanet;       // Радиус планеты
    double radiusOfOrbit;        // Радиус ордиты
    coordinate_X_Y coordinate;   // Координаты центра планеты

    sector **massOfSectors;   // Массив секторов
};

#endif // PLANET_H
