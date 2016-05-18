//
//  Building_Sprite.hpp
//  space
//
//  Created by fix on 18/05/16.
//
//

#ifndef Building_Sprite_hpp
#define Building_Sprite_hpp

#include <stdio.h>
#include "building.h"
class Building_Sprite: public cocos2d::Sprite{
public:
    
    building* building_in_sprite;
    
    static Building_Sprite *create();
    void initOptions(Building_Sprite*);
    
    void set_building_sprite(building* cur_unit);
    building* get_building_in_sprite();
    void set_id(int num);
};
#endif /* Building_Sprite_hpp */
