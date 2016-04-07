#ifndef PLANET_H
#define PLANET_H

#include "sector.h"

class planet: public GameSprite{

public:
    planet();   // Констуктор по умолчанию создает планету с координатами (0, 0)
    double get_planet_radius();
    double get_radius_orbit();
    coordinate_X_Y get_planet_coordinates();
    sector** getMassOfSectors();
    static planet* create ();

private:
    double radiusOfPlanet;       // Радиус планеты
    double radiusOfOrbit;        // Радиус ордиты
    coordinate_X_Y coordinate;   // Координаты центра планеты
    sector **massOfSectors;   // Массив секторов
};

#endif // PLANET_H
