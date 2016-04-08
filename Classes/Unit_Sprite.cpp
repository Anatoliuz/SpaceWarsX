//
//  Unit_Sprite.cpp
//  space
//
//  Created by fix on 08/04/16.
//
//

#include "Unit_Sprite.hpp"
Unit_Sprite* Unit_Sprite::create(){
    Unit_Sprite * sprite = new Unit_Sprite();
    if (sprite->initWithFile("rocket.png")) {
        sprite->autorelease();
        sprite->initOptions(sprite);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
void Unit_Sprite::initOptions(Unit_Sprite* unit_sprite){
    unit_in_sprite = new unit();
    coordinate_X_Y unit_coords = unit_in_sprite->get_unit_coordinates();
    unit_sprite->setPosition(cocos2d::Vec2(unit_coords.x,unit_coords.y));
    unit_sprite->setScaleX(unit_in_sprite->get_unit_width()/unit_sprite->getContentSize().width);
    unit_sprite->setScaleY(unit_in_sprite->get_unit_height()/unit_sprite->getContentSize().height);
}