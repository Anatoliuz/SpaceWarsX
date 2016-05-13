//
//  Building_Sprite.hpp
//  space
//
//  Created by fix on 11/05/16.
//
//

#ifndef Building_Sprite_hpp
#define Building_Sprite_hpp

#include <stdio.h>
#include "building.h"

class Building_Sprite: public cocos2d::Sprite{
public:
    building* building_in_sprite;
    static Building_Sprite  *create();
    static Building_Sprite *create(double x, double y);
    void addEvents(Building_Sprite* sprite);
    
    //Метод, который вызывается при "прикосновении" к этому объекту
    void touchEvent(cocos2d::Touch* touch);
    void initOptions(Building_Sprite*);
};

#endif /* Building_Sprite_hpp */
