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
#include "ui/CocosGUI.h"
#include "Building_Sprite.hpp"
#include "client.h"
#include "Network.h"
#include "calcModAdapter.h"
enum {
    kBackground,
    kMiddleground,
    kForeground,
    kUnit,
    kBuilding,
    kShell
};

enum {
    kSpriteRocket,
    kSpritePlanet,
    kSpriteBoost,
    kSpriteStar,
    
};

typedef enum gamestates {
    kGameIntro,
    kGamePaused,
    kGamePlay,
    kGameOver
    
}GameState;

class HelloWorld : public cocos2d::Layer
{
public:
    void manage_units();
    
    void set_planets();
    void set_background();
    CREATE_FUNC(HelloWorld);
    static HelloWorld* get_instance();
    sector **planet_sector;
    void set_max_unit_index(int number);
    void Manage_Planets();
    
    
    
    vector<Planet_Sprite*> planet_sprite;
    
    vector<Unit_Sprite*> unit_sprite;
    vector<Building_Sprite*> building_sprite;
    
    calculationMod* calculator;
    vector<building> tempo;
    vector<planet> vectOfPlanets;
    vector<rib> vectOfRibs;
    vector<shell> vectorOfShells;
    vector<building> vectOfBuildings;
//    Client* client;
    
    Planet_Sprite* get_planet_sprite_by_id(int i);
    
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

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    void toGameScene();
    void  transitionToGameScene();
    void startGame();
    void draw_shells();
private:
    std::list<unit> *list_units;
    std::list<ribStruct> *list_units_ribs;
    cocos2d::Label* labelTouchInfo;
    coordinate_X_Y mouse_coords;
    static HelloWorld* layer;
    int max;
    controller* my_controller;
    client<calcModAdapter, Network>* my_client;
};

#endif // __HELLOWORLD_SCENE_H__
