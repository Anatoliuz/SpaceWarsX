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

    unit *temp = new unit(0, 0);
   // unit_sprite->setPosition(cocos2d::Vec2(unit_coords.x,unit_coords.y));
  //  float a =unit_sprite->getContentSize().width;
    unit_sprite->setScaleX(temp->get_unit_width()/unit_sprite->getContentSize().width);
    unit_sprite->setScaleY(temp->get_unit_height()/unit_sprite->getContentSize().height);
    delete temp;
}

void Unit_Sprite::set_unit_sprite(unit* cur_unit){
    unit_in_sprite = cur_unit;
}
unit* Unit_Sprite::get_unit_in_sprite(){
    return unit_in_sprite;
}