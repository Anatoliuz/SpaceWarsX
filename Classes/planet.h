#ifndef PLANET_H
#define PLANET_H

#include <sector.h>
#include "cocos2d.h"

class planet:public cocos2d::Sprite{

public:
    planet();   // Констуктор по умолчанию создает планету с координатами (0, 0)
    static planet* create();
    sector** getMassOfSectors();

private:
    double radiusOfPlanet;       // Радиус планеты
    double radiusOfOrbit;        // Радиус ордиты
    coordinate_X_Y coordinate;   // Координаты центра планеты

    sector **massOfSectors;   // Массив секторов
};

#endif // PLANET_H
