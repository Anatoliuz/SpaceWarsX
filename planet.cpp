#include "planet.h"
#include <math.h>
#include "cocos2d.h"
using namespace cocos2d;


planet::planet()
{
    //размер экрана
    CCSize win_size = CCDirector::sharedDirector()->getWinSize();
    radiusOfPlanet = 100;
    radiusOfOrbit = 50;
    
//   координаты в центре
    coordinate.x = win_size.width/2;
    coordinate.y = win_size.height/2;

    double straightLine = radiusOfPlanet - radiusOfOrbit / 2;
    double diagonal = straightLine / sqrt(2);
    double diagonalDifference = radiusOfOrbit / sqrt(2);

    int numbOfOrbits = 5;
    int numbOfOrbitParts = 8;
    massOfSectors = new sector*[numbOfOrbits];
    for (int i = 0; i < numbOfOrbits; i++){
         massOfSectors[i] = new sector[numbOfOrbitParts];
     }

    for (int i = 0; i < 5; i++){
        straightLine += radiusOfOrbit;
        diagonal += diagonalDifference;

        double bigDifference = diagonal;
        double smallDifference = straightLine - diagonal;

        massOfSectors[i][0] = sector(coordinate.x, coordinate.y, bigDifference, -smallDifference);
        massOfSectors[i][1] = sector(coordinate.x, coordinate.y, smallDifference, -bigDifference);
        massOfSectors[i][2] = sector(coordinate.x, coordinate.y, -smallDifference, -bigDifference);
        massOfSectors[i][3] = sector(coordinate.x, coordinate.y, -bigDifference, -smallDifference);
        massOfSectors[i][4] = sector(coordinate.x, coordinate.y, -bigDifference, smallDifference);
        massOfSectors[i][5] = sector(coordinate.x, coordinate.y, -smallDifference, bigDifference);
        massOfSectors[i][6] = sector(coordinate.x, coordinate.y, smallDifference, bigDifference);
        massOfSectors[i][7] = sector(coordinate.x, coordinate.y, bigDifference, smallDifference);

        massOfSectors[i][0].changeCoordinates(0, straightLine, diagonal, diagonal);
        massOfSectors[i][1].changeCoordinates(diagonal, diagonal, straightLine, 0);
        massOfSectors[i][2].changeCoordinates(straightLine, 0, diagonal, -diagonal);
        massOfSectors[i][3].changeCoordinates(diagonal, -diagonal, 0, -straightLine);
        massOfSectors[i][4].changeCoordinates(0, -straightLine, -diagonal, -diagonal);
        massOfSectors[i][5].changeCoordinates(-diagonal, -diagonal, -straightLine, 0);
        massOfSectors[i][6].changeCoordinates(-straightLine, 0, -diagonal, diagonal);
        massOfSectors[i][7].changeCoordinates(-diagonal, diagonal, 0, straightLine);
    }

    // Отладочные юниты
    massOfSectors[0][0].createUnit1();
    massOfSectors[0][0].createUnit2();
}

sector** planet::getMassOfSectors(){
    return massOfSectors;
}
double planet::get_planet_radius(){
    return radiusOfPlanet;
}
coordinate_X_Y planet::get_planet_coordinates(){
    return coordinate;
}

planet* planet::create () {

	planet * sprite = new planet();
	if (sprite && sprite->initWithFile("my_planet.png")) {
		sprite->autorelease();
        sprite->setRadius(sprite->boundingBox().size.height * 0.5f);//!!!
        return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}