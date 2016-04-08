//
//  Planet_Sprite.cpp
//  space
//
//  Created by fix on 08/04/16.
//
//

#include "Planet_Sprite.hpp"


Planet_Sprite* Planet_Sprite::create(){
    Planet_Sprite * sprite = new Planet_Sprite();
    if (sprite->initWithFile("planet.png")) {
        sprite->autorelease();
        sprite->initOptions(sprite);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void Planet_Sprite::initOptions(Planet_Sprite* planet_sprite){
    planet_in_sprite = new planet();
    Planet_Sprite myplanet;
    coordinate_X_Y planet_coord = planet_in_sprite->get_planet_coordinates();
    planet_sprite->setPosition(cocos2d::Vec2(planet_coord.x,planet_coord.y));
    planet_sprite->setScaleX(planet_in_sprite->get_planet_radius()/planet_sprite->getContentSize().width);
    planet_sprite->setScaleY(planet_in_sprite->get_planet_radius()/planet_sprite->getContentSize().height);
}