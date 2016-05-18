//
//  Planet_Sprite.hpp
//  space
//
//  Created by fix on 08/04/16.
//
//

#ifndef Planet_Sprite_hpp
#define Planet_Sprite_hpp

#include "planet.h"
#include "ui/CocosGUI.h"
class Planet_Sprite: public cocos2d::Sprite{


public:
    planet* planet_in_sprite;
    static Planet_Sprite *create();
    static Planet_Sprite *create(double x, double y);
    void addEvents(Planet_Sprite* sprite);
    
    

    void set_planet(planet*);
    planet* get_planet();

    //Метод, который вызывается при "прикосновении" к этому объекту
    void touchEvent(cocos2d::Touch* touch);
    void initOptions(Planet_Sprite*);
    
    
private:
    //vector<unit> vectOfUnits;
};
#endif /* Planet_Sprite_hpp */
