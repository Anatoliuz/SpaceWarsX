#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#define GOAL_WIDTH 400
#include "cocos2d.h"
#include "GameSprite.h"
using namespace cocos2d;

class GameLayer : public cocos2d::CCLayer
{
public:
    ~GameLayer();
    virtual bool init();
    static CCScene *createScene();
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameLayer);

    //virtual void ccTouchesBegan(CCSet* pTouches,
                              //  CCEvent* event);
    //virtual void ccTouchesMoved(CCSet* pTouches,
                               // CCEvent* event);
    //virtual void ccTouchesEnded(CCSet* pTouches,
                                //CCEvent* event);
      void update(float dt);

private:
    GameSprite * _player1;
    GameSprite * _player2;
    GameSprite * _player3_ball;

    CCArray * _players;
    CCLabelTTF * _player1ScoreLabel;
    CCLabelTTF * _player2ScoreLabel;

    CCSize _screenSize;
    int _player1Score;
    int _player2Score;
    void playerScore(int player);
};

#endif // __HELLOWORLD_SCENE_H__
