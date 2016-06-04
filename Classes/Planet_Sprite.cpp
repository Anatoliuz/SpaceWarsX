#include "Planet_Sprite.hpp"
#include "HelloWorldScene.h"

using namespace cocos2d;
Player_Info dataaa;

planet* Planet_Sprite::get_planet(){
    return planet_in_sprite;
}

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
    touchListener->onTouchBegan = [&](Touch* touch, Event* event) -> bool {
        
        auto bounds = event->getCurrentTarget()->getBoundingBox();
        
        if (bounds.containsPoint(touch->getLocation())){
            
//                auto button = ui::Button::create("hammer.png", "hammer.png", "hammer.png");
//                
//                //button->setTitleText("Button Text");
//                
//                button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
//                    switch (type)
//                    {
//                        case ui::Widget::TouchEventType::BEGAN:
//                            break;
//                        case ui::Widget::TouchEventType::ENDED:
//                            this->removeAllChildren();
//                            
//                            // std::cout << "Button 1 clicked" << std::endl;
//                            break;
//                        default:
//                            break;
//                    }
//                });
//                button->Node::setPosition(0,0);
//                
//                button->cocos2d::Node::setScale(0.7);
//                this->addChild(button,6);
            touched = true;
                return true;
            
            
        }
        
        return true;
    };
    touchListener->onTouchCancelled = [this](Touch* touch, Event* event) -> bool {
        //  this->removeAllChildren();
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
void Planet_Sprite::set_touch(bool in)
{
    touched = in;
}

bool Planet_Sprite::is_touched(){
    return touched;
}