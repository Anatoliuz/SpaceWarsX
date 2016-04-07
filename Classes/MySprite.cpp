//
//  MySprite.cpp
//  space
//
//  Created by fix on 07/04/16.
//
//

#include "MySprite.hpp"

using namespace cocos2d;

MySprite::MySprite() {}

MySprite::~MySprite() {}

MySprite* MySprite::create()
{
    MySprite* pSprite = new MySprite();
    
    if (pSprite->initWithFile("planet.png"))
    {
        pSprite->autorelease();
        
        pSprite->initOptions();
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void MySprite::initOptions()
{
    // do things here like setTag(), setPosition(), any custom logic.
}

