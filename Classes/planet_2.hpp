//
//  planet_2.hpp
//  space
//
//  Created by fix on 08/04/16.
//
//
#include "cocos2d.h"
#include "sector.h"
#include <math.h>
class planet_2 : public cocos2d::Sprite
{
public:
    planet_2();
    ~planet_2();
    static planet_2* create();
    
    void initOptions();
    
    void addEvents();
    //  void touchEvent(cocos2d::Touch* touch, cocos2d::Vector2 _p);
    // Констуктор по умолчанию создает планету с координатами (0, 0)
    double get_planet_radius();
    double get_radius_orbit();
    coordinate_X_Y get_planet_coordinates();
    sector** getMassOfSectors();
    
    
private:
    double radiusOfPlanet;       // Радиус планеты
    double radiusOfOrbit;        // Радиус ордиты
    coordinate_X_Y coordinate;   // Координаты центра планеты
    sector **massOfSectors;
};
