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
#include "Player_Info.hpp"

class Planet_Sprite: public cocos2d::Sprite{

private:
    bool touched;
public:
    planet* planet_in_sprite;
    static Planet_Sprite *create();
    static Planet_Sprite *create(double x, double y);
    void addEvents(Planet_Sprite* sprite);
    bool is_touched();
    void set_touch(bool);
    void set_planet(planet*);
    planet* get_planet();

    //Метод, который вызывается при "прикосновении" к этому объекту
    void touchEvent(cocos2d::Touch* touch);
    void initOptions(Planet_Sprite*);

};
#endif /* Planet_Sprite_hpp */
