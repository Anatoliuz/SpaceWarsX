#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Rocket.h"
#include "planet.h"
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
public:
    //Rocket* _rocket;
    planet* _planet;
    static cocos2d::Scene* createScene();

    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    CC_SYNTHESIZE(cocos2d::Size, _screenSize, set_size);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
