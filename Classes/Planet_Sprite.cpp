//
//  Planet_Sprite.cpp
//  space
//
//  Created by fix on 08/04/16.
//
//

#include "Planet_Sprite.hpp"
Player_Info dataaa;

using namespace cocos2d;
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
            if (planet_in_sprite->getOwner() == dataaa.player_num) {
                dataaa.players_planet_touched = true;
                auto button = ui::Button::create("hammer.png", "hammer.png", "hammer.png");
                
                //button->setTitleText("Button Text");
                
                button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
                    switch (type)
                    {
                        case ui::Widget::TouchEventType::BEGAN:
                            break;
                        case ui::Widget::TouchEventType::ENDED:
                            this->removeAllChildren();
                            
                            // std::cout << "Button 1 clicked" << std::endl;
                            break;
                        default:
                            break;
                    }
                });
                button->Node::setPosition(0,0);
                
                button->cocos2d::Node::setScale(0.7);
                this->addChild(button,6);
                return true;
            }
            
            std::stringstream touchDetails;
            touchDetails << "Touched at OpenGL coordinates: " <<
            touch->getLocation().x << "," << touch->getLocation().y << std::endl <<
            "Touched at UI coordinate: " <<
            touch->getLocationInView().x << "," << touch->getLocationInView().y << std::endl <<
            "Touched at local coordinate:" <<
            event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).x << "," <<
            event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).y << std::endl <<
            "Touch moved by:" << touch->getDelta().x << "," << touch->getDelta().y;
           
            auto button = ui::Button::create("attack.png", "attack.png", "attack.png");
            
            //button->setTitleText("Button Text");
            
            button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
                switch (type)
                {
                    case ui::Widget::TouchEventType::BEGAN:
                        break;
                    case ui::Widget::TouchEventType::ENDED:
                        this->removeAllChildren();

                        // std::cout << "Button 1 clicked" << std::endl;
                        break;
                    default:
                        break;
                }
            });
            button->Node::setPosition(0,0);

            button->cocos2d::Node::setScale(0.7);
            this->addChild(button,6);
            
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
