#ifndef __GAME_SPRITE_H__
#define __GAME_SPRITE_H__

#include "cocos2d.h"
using namespace cocos2d;
class GameSprite : public CCSprite
{
public:
   CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
   CC_SYNTHESIZE(CCPoint, _vector, Vector);
   CC_SYNTHESIZE(CCPoint *, _touch, Touch);

    GameSprite(void);
    ~GameSprite(void);

    static GameSprite * gameSpriteWithFile(const char * pszFileName);

    virtual void setPosition(const CCPoint& pos);
    // a selector callback
    float radius();
    // implement the "static create()" method manually
};

#endif // __HELLOWORLD_SCENE_H__
