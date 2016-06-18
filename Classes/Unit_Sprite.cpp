//
//  Unit_Sprite.cpp
//  space
//
//  Created by fix on 08/04/16.
//
//

#include "Unit_Sprite.hpp"

Unit_Sprite* Unit_Sprite::create(int owner){
    Unit_Sprite * sprite = new Unit_Sprite();
    if (owner == 0) {
    if (sprite->initWithFile("ufo_0.png")) {
        sprite->autorelease();
        sprite->initOptions(sprite, owner);
        return sprite;
    }
    }
    else {
        if (sprite->initWithFile("ufo_2.png")) {
            sprite->autorelease();
            sprite->initOptions(sprite, owner);
            return sprite;
        }

    }
    
    CC_SAFE_DELETE(sprite);
    return NULL;
}
void Unit_Sprite::initOptions(Unit_Sprite* unit_sprite, int owner){

    unit *temp = new unit(0, 0, 1, owner); //!!!
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