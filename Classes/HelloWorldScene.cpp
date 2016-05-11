#include "HelloWorldScene.h"
USING_NS_CC;

int num_of_planetss = 2;
int num_of_playerss = 2;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size screenSize = CCDirector::sharedDirector()->getWinSize();
    Point center = Point(screenSize.width/2 + origin.x, screenSize.height/2 + origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("SpaceWarsX", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    // add "HelloWorld" splash screen"

    // add the sprite as a child to this layer
   
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("untitled.tmx");
    _background = _tileMap->layerNamed("Background");
    
    this->addChild(_tileMap);
    planets_array = new Planet_Sprite*[num_of_planetss]();
    for (int i = 0; i < num_of_planetss; ++i) {
        planets_array[i] = new Planet_Sprite();
    }
    planets_array[0] =  Planet_Sprite::create() ;
    this->addChild(planets_array[0], kMiddleground);

    planets_array[1] =  Planet_Sprite::create(500, 500) ;
    this->addChild(planets_array[1], kMiddleground);

    
//    auto sprite = Sprite::create("HelloWorld.png");
//    sprite->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
//                             Director::getInstance()->getVisibleSize().height / 2));
//    
//    // Add a "touch" event listener to our sprite
//    
//    this->addChild(sprite, 0);
    
    unit_sprite_1 = Unit_Sprite::create();
    unit_sprite_2 = Unit_Sprite::create();
    
    massOfPlanets = new planet[num_of_planetss];
    for (int i = 0; i < num_of_planetss; ++i) {
        massOfPlanets[i] = *(planets_array[i]->planet_in_sprite);
    }

    rockets_to_print = massOfPlanets->getMassOfSectors();
//    std::list<unit> list_units = rockets_to_print[0][0]->getMassOfPlayersLists;
//    calculator = new calculationMod();
//    //std::list<unit>* list_units = rockets_to_print.getMassOfPlayersLists();
//    
//    while(!list_units->empty()) {
//        unit_sprite_1->set_unit_sprite(&list_units.front());
//        unit temp_unit =  list_units.front();
//        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
//        unit_sprite_1->setPosition(Vec2(coords.x, coords.y));
//        list_units.pop_back();
//        this->addChild(unit_sprite_1, kMiddleground);
//    }

   
   // this->scheduleUpdate();

    return true;
}
//delta позволяет  сгладить  движения объектов в loop'e
void HelloWorld::update(float delta){

//    calculator->doStep(massOfPlanets, num_of_planets);
//
//
//        for (int j = 0; j < 8; j++){
//            list_units_1 =  rockets_to_print[0][j].getListOfUnits1();
//            while(!list_units_1.empty()) {
//                unit temp_unit =  list_units_1.front();
//                coordinate_X_Y coords = temp_unit.get_unit_coordinates();
//                unit_sprite_1->setPosition(coords.x, coords.y);
//                list_units_1.pop_front();
//            }
//       }
//    
//    for (int j = 0; j < 8; j++){
//        list_units_2 =  rockets_to_print[0][j].getListOfUnits2();
//        while(!list_units_2.empty()) {
//            unit temp_unit =  list_units_2.front();
//            coordinate_X_Y coords = temp_unit.get_unit_coordinates();
//            unit_sprite_2->setPosition(coords.x, coords.y);
//            list_units_2.pop_front();
//        }
//    }
    
    
//    auto position = _planet->getPosition();
//    position.x -= 250 * delta;
//    if (position.x  < 0 - (_planet->getBoundingBox().size.width / 2))
//        position.x = this->getBoundingBox().getMaxX() + _planet->getBoundingBox().size.width/2;
//    _planet->setPosition(position);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    labelTouchInfo->setPosition(touch->getLocation());
    labelTouchInfo->setString("You Touched Here");
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    cocos2d::log("touch ended");
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}

