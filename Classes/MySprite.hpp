//
//  MySprite.hpp
//  space
//
//  Created by fix on 07/04/16.
//
//

#ifndef MySprite_hpp
#define MySprite_hpp



#include "cocos2d.h"

class MySprite : public cocos2d::Sprite
{
public:
    MySprite();
    ~MySprite();
    static MySprite* create();
    
    void initOptions();
    
    void addEvents();
  //  void touchEvent(cocos2d::Touch* touch, cocos2d::Vector2 _p);
    
private:
    
};

#endif // _MYSPRITE_HPP_
