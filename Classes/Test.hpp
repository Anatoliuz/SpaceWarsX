//
//  Test.hpp
//  space
//
//  Created by fix on 23/05/16.
//
//

#ifndef Test_hpp
#define Test_hpp


#include "controller.h"
class Singleton{
public:
    static Singleton* get_instance(){
        _self = new Singleton();
    }
private:
    static Singleton *_self;
};
#endif /* Test_hpp */
