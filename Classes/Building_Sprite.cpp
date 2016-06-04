//
//  Building_Sprite.cpp
//  space
//
//  Created by fix on 18/05/16.
//
//

#include "Building_Sprite.hpp"

using namespace cocos2d;
Building_Sprite* Building_Sprite::create(){
    Building_Sprite * sprite = new Building_Sprite();
    if (sprite->initWithFile("building.png")) {
        sprite->autorelease();
        sprite->initOptions(sprite);
     //   sprite->addEvents(sprite);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}


void Building_Sprite::initOptions(Building_Sprite* building_sprite){
    coordinate_X_Y coord;
    coord.x = 0;
    coord.y = 0;
    building *temp = new building(coord, 0, 0, 0);//!!!
    building_sprite->setScaleX(temp->get_width()/building_sprite->getContentSize().width);
    building_sprite->setScaleY(temp->get_height()/building_sprite->getContentSize().height);
    
    delete temp;
}

void Building_Sprite::set_building_sprite(building* cur_unit){
    building_in_sprite = cur_unit;
}
building* Building_Sprite::get_building_in_sprite(){
    return building_in_sprite;
}