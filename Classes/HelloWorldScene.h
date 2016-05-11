#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include <iostream>
#include "cocos2d.h"
#include "sector.h"
#include "calculationmod.h"
#include "coordinate_x_y.h"
#include "Planet_Sprite.hpp"
#include "Unit_Sprite.hpp"
#include "SimpleAudioEngine.h"
#include "Building_Sprite.hpp"
enum {
    kBackground,
    kMiddleground,
    kForeground
};

enum {
    kSpriteRocket,
    kSpritePlanet,
    kSpriteBoost,
    kSpriteStar
};

typedef enum gamestates {
    kGameIntro,
    kGamePaused,
    kGamePlay,
    kGameOver
    
}GameState;

class HelloWorld : public cocos2d::Layer
{
private:
    std::list<unit> list_units_1;
    std::list<unit> list_units_2;
    cocos2d::Label* labelTouchInfo;
    coordinate_X_Y mouse_coords;

public:
    CREATE_FUNC(HelloWorld);
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    
   // Planet_Sprite* planet_sprite[num_of_players];
    Unit_Sprite* unit_sprite;
    
    Unit_Sprite* unit_sprite_2;
    //std::vector<Planet_Sprite> planet_sprite;
    Planet_Sprite** planets_array;
    //Planet_Sprite* planet_sprite_2;

    
    calculationMod* calculator;
    sector **planet_sector;
    planet *massOfPlanets;
   
    
    static cocos2d::Scene* createScene();
    void update(float) override;
    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool isLeftButtonPressed();
    
    coordinate_X_Y getMouseCoordinates();
    CC_SYNTHESIZE(cocos2d::Size, _screenSize, set_size);
    // implement the "static create()" method manually
    
    cocos2d::CCSpriteBatchNode *_gameBatchNode;
    cocos2d::CCParticleSystem * _jet;
    
    cocos2d:: CCTMXTiledMap *_tileMap;
    cocos2d::CCTMXLayer *_background;

};

#endif // __HELLOWORLD_SCENE_H__
