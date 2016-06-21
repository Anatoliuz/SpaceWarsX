//
//  EndGameScene.hpp
//  space
//
//  Created by fix on 21/06/16.
//
//

#ifndef EndGameScene_hpp
#define EndGameScene_hpp



#include "cocos2d.h"

class EndGameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EndGameScene);
};



#endif /* EndGameScene_hpp */
