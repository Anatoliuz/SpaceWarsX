//
//  EndGameScene.hpp
//  space
//
//  Created by fix on 21/06/16.
//
//

#ifndef EndGameScene_hpp
#define EndGameScene_hpp



#include "AppDelegate.h"

class EndGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(bool);
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EndGameScene);
private:
    static bool is_win;
};



#endif /* EndGameScene_hpp */
