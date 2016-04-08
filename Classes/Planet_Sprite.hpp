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

class Planet_Sprite: public cocos2d::Sprite{
public:
    planet* planet_in_sprite;
    static Planet_Sprite *create();
    void initOptions(Planet_Sprite*);
};
#endif /* Planet_Sprite_hpp */
