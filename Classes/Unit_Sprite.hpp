//
//  Unit_Sprite.hpp
//  space
//
//  Created by fix on 08/04/16.
//
//

#ifndef Unit_Sprite_hpp
#define Unit_Sprite_hpp

#include "unit.h"
class Unit_Sprite: public cocos2d::Sprite{
public:
    unit* unit_in_sprite;
    static Unit_Sprite *create();
    void initOptions(Unit_Sprite*);
};

#endif /* Unit_Sprite_hpp */
