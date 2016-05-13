//
//  Building_Sprite.cpp
//  space
//
//  Created by fix on 11/05/16.
//
//

#include "Building_Sprite.hpp"
using namespace cocos2d;
Building_Sprite* Building_Sprite::create(){
    Building_Sprite * sprite = new Building_Sprite();
    if (sprite->initWithFile("HelloWorld.png")) {
        sprite->autorelease();
        sprite->initOptions(sprite);
        sprite->addEvents(sprite);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
Building_Sprite* Building_Sprite::create(double x, double y){
    Building_Sprite * sprite = new Building_Sprite();
    
    if (sprite->initWithFile("HelloWorld.png")) {
        sprite->autorelease();
        sprite->initOptions(sprite);
        sprite->setPosition(x, y);
        sprite->addEvents(sprite);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
void Building_Sprite::addEvents(Building_Sprite* sprite){
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* touch, Event* event) -> bool {
        
        auto bounds = event->getCurrentTarget()->getBoundingBox();
        
        if (bounds.containsPoint(touch->getLocation())){
            std::stringstream touchDetails;
            touchDetails << "Touched at OpenGL coordinates: " <<
            touch->getLocation().x << "," << touch->getLocation().y << std::endl <<
            "Touched at UI coordinate: " <<
            touch->getLocationInView().x << "," << touch->getLocationInView().y << std::endl <<
            "Touched at local coordinate:" <<
            event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).x << "," <<
            event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).y << std::endl <<
            "Touch moved by:" << touch->getDelta().x << "," << touch->getDelta().y;
            
            MessageBox(touchDetails.str().c_str(), "Touched");
        }
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,sprite);
}
void Building_Sprite::initOptions(Building_Sprite* building_sprite){
    building_in_sprite = new building();
    Building_Sprite myplanet;
    coordinate_X_Y building_coords = building_in_sprite->getCoordinate();
    building_sprite->setPosition(cocos2d::Vec2(building_coords.x,building_coords.y));
//    
//    building_sprite->setScaleX(building_in_sprite->get_planet_radius()/building_sprite->getContentSize().width);
//    building_sprite->setScaleY(building_in_sprite->get_planet_radius()/building_sprite->getContentSize().height);
}