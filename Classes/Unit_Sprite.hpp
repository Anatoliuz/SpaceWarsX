//
//  Unit_Sprite.hpp
//  space
//
//  Created by fix on 08/04/16.
//
//

#ifndef Unit_Sprite_hpp
#define Unit_Sprite_hpp

#include "unit.h"
#include <list>
#include "sector.h"
#include "rib.h"
class Unit_Sprite: public cocos2d::Sprite{
private:
    int unit_sprite_id;
    
public:
   
    unit* unit_in_sprite;
    
    static Unit_Sprite *create(int owner);
    void initOptions(Unit_Sprite*, int owner);
    void set_unit_sprite(unit* cur_unit);
    unit* get_unit_in_sprite();
    //void set_unit_sprite_from_rib(ribStruct *unit);
    
    void set_id(int num);
};

#endif /* Unit_Sprite_hpp */
