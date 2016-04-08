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
class Unit_Sprite: public cocos2d::Sprite{
    
public:
   
    sector **rockets_to_print;
    std::list<unit> list_units_1;
    unit* unit_in_sprite;
    
    static Unit_Sprite *create();
    void initOptions(Unit_Sprite*);
    void set_unit_sprite(unit* cur_unit);
    unit* get_unit_in_sprite();
};

#endif /* Unit_Sprite_hpp */
