#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#define GOAL_WIDTH 400
#include "cocos2d.h"
#include "GameSprite.h"
using namespace cocos2d;

class GameLayer : public cocos2d::CCLayer
{
private:
    GameSprite * player1;
    GameSprite * player2;
    GameSprite * ball;

    CCArray* players;

    CCSize screenSize;


public:
    ~GameLayer();
    static Scene* scene();

   virtual bool init();
   void menuCloseCallback(Ref* pSender);

   CREATE_FUNC(GameLayer);
  // virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
  // virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);

  // virtual void ccTouchEnded(CCSet* pTouches, CCEvent* event);
   void update(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
