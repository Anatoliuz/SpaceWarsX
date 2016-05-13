//
//  Planet_Sprite.cpp
//  space
//
//  Created by fix on 08/04/16.
//
//

#include "Planet_Sprite.hpp"

using namespace cocos2d;
Planet_Sprite* Planet_Sprite::create(){
    Planet_Sprite * sprite = new Planet_Sprite();
    if (sprite->initWithFile("planet.png")) {
        sprite->autorelease();
        sprite->initOptions(sprite);
        sprite->addEvents(sprite);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
Planet_Sprite* Planet_Sprite::create(double x, double y){
    Planet_Sprite * sprite = new Planet_Sprite();
  
    if (sprite->initWithFile("planet.png")) {
        sprite->autorelease();
        sprite->initOptions(sprite);
        sprite->setPosition(x, y);
        sprite->addEvents(sprite);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
void Planet_Sprite::addEvents(Planet_Sprite* sprite){
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* touch, Event* event) -> bool {
        
//        auto bounds = event->getCurrentTarget()->getBoundingBox();
//        
//        if (bounds.containsPoint(touch->getLocation())){
//            std::stringstream touchDetails;
//            touchDetails << "Touched at OpenGL coordinates: " <<
//            touch->getLocation().x << "," << touch->getLocation().y << std::endl <<
//            "Touched at UI coordinate: " <<
//            touch->getLocationInView().x << "," << touch->getLocationInView().y << std::endl <<
//            "Touched at local coordinate:" <<
//            event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).x << "," <<
//            event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).y << std::endl <<
//            "Touch moved by:" << touch->getDelta().x << "," << touch->getDelta().y;
//            //MessageBox(touchDetails.str().c_str(), "Touched");
//
//        }
//        return true;
    };
   
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,sprite);
}
void Planet_Sprite::initOptions(Planet_Sprite* planet_sprite){
    planet_in_sprite = new planet();
    Planet_Sprite myplanet;
    coordinate_X_Y planet_coord = planet_in_sprite->get_planet_coordinates();
    planet_sprite->setPosition(cocos2d::Vec2(planet_coord.x,planet_coord.y));
    planet_sprite->setScaleX(planet_in_sprite->get_planet_radius()/planet_sprite->getContentSize().width);
    planet_sprite->setScaleY(planet_in_sprite->get_planet_radius()/planet_sprite->getContentSize().height);
}
void Planet_Sprite::set_planet(planet* planet){
    planet_in_sprite = planet;
}
planet* Planet_Sprite::get_planet(){
    return planet_in_sprite;
}
