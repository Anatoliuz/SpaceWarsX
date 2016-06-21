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
    kShell,
    kButton,
    kRibs
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
  
    static HelloWorld* get_instance();
    static cocos2d::Scene* createScene();

    sector **planet_sector;
    calculationMod* calculator;

    void set_max_unit_index(int number);
    void manage_planets();
    void manage_units();
    void set_planets();
    void set_background();
    void update(float) override;
    void draw_buildings_on_planet();
    void clear_buttons(Planet_Sprite*);
    void draw_ribs();
    
    vector<Planet_Sprite*> planet_sprite;
    vector<Unit_Sprite*> unit_sprite;
    vector<Building_Sprite*> building_sprite;
    vector<building> tempo;
    vector<planet> vectOfPlanets;
    vector<rib> vectOfRibs;
    vector<shell> vectorOfShells;
    vector<building> vectOfBuildings;
    
    Planet_Sprite* get_planet_sprite_by_id(int i);
    void draw_shells();
    virtual bool init();
    coordinate_X_Y getMouseCoordinates();
    bool isLeftButtonPressed();

    
    void toGameScene();
    void  transitionToGameScene();
    void startGame();
    
    CC_SYNTHESIZE(cocos2d::Size, _screenSize, set_size);
    // implement the "static create()" method manually
    void menuCloseCallback(cocos2d::Ref* pSender);

    cocos2d::CCSpriteBatchNode *_gameBatchNode;
    cocos2d::CCParticleSystem * _jet;
    
    cocos2d:: CCTMXTiledMap *_tileMap;
    cocos2d::CCTMXLayer *_background;
    CREATE_FUNC(HelloWorld);

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
 
    int draw_win();
    
private:
    int num_of_planets;
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
