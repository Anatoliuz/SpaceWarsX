#include "HelloWorldScene.h"
USING_NS_CC;

int num_of_planetss = 2;
int num_of_playerss = 2;
bool left_button_state = false;
coordinate_X_Y mouseCoords;
double mouse_x = 0;
double mouse_y = 0;

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
    left_button_state = false;
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
    
  //  sector **rockets_to_print = massOfPlanets[0].getMassOfSectors();
   // planet_sector = massOfPlanets[0].getMassOfSectors();
    
    unit_sprite = Unit_Sprite::create();
    unit_sprite_2 = Unit_Sprite::create();
    
    massOfPlanets = new planet[num_of_planetss];
    for (int i = 0; i < num_of_planetss; ++i) {
        massOfPlanets[i] = *(planets_array[i]->planet_in_sprite);
    }
    

 //   rockets_to_print = massOfPlanets->getMassOfSectors();
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
    vector<planet> vectOfPlanets;
    vector<rib> vectOfRibs;
    
    //planet firstPlanet = planet(0, 0.0, 0.0, 4);
    //    double ee = 0.554;
    //    double rr = 0.3232;
    //    int yy = 0;
    //    int pp = 4;
    vectOfPlanets.push_back(planet(0, 0, 0, 4));
    vectOfPlanets.push_back(planet(1, 600, 2000, 4));
    vectOfPlanets.push_back(planet(2, -600, 2000, 4));
    //massOfPlanets[0] = planet(0, 0, 0, 4);
    //massOfPlanets[1] = planet(1, 400, 400, 4);
    //massOfRibs[0] = rib(massOfPlanets[0], massOfPlanets[1], 4);
    //massOfRibs[0] = rib(vectOfPlanets[0], vectOfPlanets[1], 4);
    
    vectOfRibs.push_back(rib(vectOfPlanets[0], vectOfPlanets[1], 4));
    vectOfRibs.push_back(rib(vectOfPlanets[0], vectOfPlanets[2], 4));
    vectOfRibs.push_back(rib(vectOfPlanets[1], vectOfPlanets[2], 4));
    
    std::cout << vectOfRibs[0].getNumb1() << vectOfRibs[0].getNumb2() << vectOfPlanets[1].getNumberOfPlanet() <<"\n\n";
    std::cout << vectOfRibs[1].getNumb1() << vectOfRibs[1].getNumb2() << vectOfPlanets[2].getNumberOfPlanet() <<"\n\n";
    
    
    vector<shell> vectorOfShells;
    
    
    calculationMod calculator;
    calculator.createBuilding(vectOfPlanets[1], 1);
    calculator.createBuilding(vectOfPlanets[2], 0);

        
        
   //     calculator.doStep(vectOfPlanets, vectOfRibs, vectorOfShells, 4);
        
        
        std::cout << "\n";
      //  calculator.changeUnitsState(vectOfPlanets[0], 1, 1, 1);
        //calculator.changeUnitsState(vectOfPlanets[0], 2, 5, 0);
      //  calculator.changeUnitsState(vectOfPlanets[2], 1, 6, 0);
        //calculator.changeUnitsState(vectOfPlanets[2], 0, 2, 0);
        
        //        if (i == 8)
        //            changeUnitsState(vectOfPlanets[1], 0, 1, 1);
        // Остановка времени на 0.1 секунду (между рендерами)
        // За рендер он будет делать достаточно большой рывок (мне так надо было для отладки)
        // Фиксится изменение параметра speed с 500 на 20 или 10 в конструкторе юнита (он находится в unit.cpp)
        //usleep (100000);
   
   this->scheduleUpdate();

    return true;
}
//delta позволяет  сгладить  движения объектов в loop'e
void HelloWorld::update(float delta){

    
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [](cocos2d::Event* event){
        try {
            EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
            mouseEvent->getMouseButton();
            std::stringstream message;
            message << "Mouse event: Button: " << mouseEvent->getMouseButton() << "pressed at point (" <<
            mouseEvent->getLocation().x << "," << mouseEvent->getLocation().y << ")";
            
            MessageBox(message.str().c_str(), "Mouse Event Details");
            
        }
        catch (std::bad_cast& e){
            // Not sure what kind of event you passed us cocos, but it was the wrong one
            return;
        }
    };
    
    listener->onMouseMove = [](cocos2d::Event* event){
        // Cast Event to EventMouse for position details like above
        try {
            EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

            mouse_x = mouseEvent->getLocation().x;
            mouse_y = mouseEvent->getLocation().y;
            cocos2d::log("%f, %f", mouse_x, mouse_y);

        }
        catch (std::bad_cast& e){
            // Not sure what kind of event you passed us cocos, but it was the wrong one
            return;
        }

        cocos2d::log("Mouse moved event");
        
    };
    
    listener->onMouseScroll = [](cocos2d::Event* event){
        cocos2d::log("Mouse wheel scrolled");
    };
    
    listener->onMouseUp = [](cocos2d::Event* event){
        cocos2d::log("Mouse button released");
        left_button_state = false;
    };
    
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
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

bool HelloWorld::isLeftButtonPressed(){
    return left_button_state;
}

coordinate_X_Y HelloWorld::getMouseCoordinates(){
    mouseCoords.x = mouse_x;
    mouseCoords.y = mouse_y;
    return mouseCoords;
}
