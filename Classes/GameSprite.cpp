#include "GameSprite.h"


GameSprite::GameSprite(void){

     _vector = ccp(0,0);


}

GameSprite::~GameSprite(){

}

GameSprite* GameSprite::gameSpriteWithFile(const char
 *pszFileName){
    GameSprite * sprite = new GameSprite();
    if(sprite && sprite->initWithFile(pszFileName)){
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void GameSprite::setPosition(const CCPoint &pos){
    CCSprite::setPosition(pos);
    if(!_nextPosition.equals(pos))
    {
        _nextPosition = pos;
    }
}

float GameSprite::radius(){
    return getTexture()->getContentSize().width * 0.5f;
}

