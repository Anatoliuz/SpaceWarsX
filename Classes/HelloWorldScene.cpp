#include "HelloWorldScene.h"

USING_NS_CC;

int num_of_planetss = 3;
int num_of_playerss = 4;
int num_of_units = 500;

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
    this->addChild(menu, 3);

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


    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [](cocos2d::Event* event){
        try {
            EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
            mouseEvent->getMouseButton();
            std::stringstream message;
            message << "Mouse event: Button: " << mouseEvent->getMouseButton() << "pressed at point (" <<
            mouseEvent->getLocation().x << "," << mouseEvent->getLocation().y << ")";
            
           // MessageBox(message.str().c_str(), "Mouse Event Details");
            
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

    planet_sprite = new Planet_Sprite*[num_of_planetss];
    for (int i = 0; i < num_of_planetss; ++i) {
        planet_sprite[i] = new Planet_Sprite();
        planet_sprite[i] = Planet_Sprite::create();
    }

   
    for (int i = 0; i < num_of_planetss; ++i) {
        planet_array = new planet[num_of_planetss]();
    }
    planet_array[0] = planet(0, 200, 200, 4);
    planet_array[1] = planet(1, 1000, 500, 4);
    planet_array[2] = planet(2, 350, 700, 4);
    vectOfPlanets.push_back(planet(0, 200, 200, 4));
    vectOfPlanets.push_back(planet(1, 1000, 500, 4));
    vectOfPlanets.push_back(planet(2, 350, 700, 4));
   
    for (int i = 0; i < num_of_planetss; ++i) {
        planet_sprite[i]->set_planet(&planet_array[i]);
        coordinate_X_Y coords = planet_array[i].getCoordinates();
        planet_sprite[i]->setPosition(coords.x, coords.y);
        this->addChild(planet_sprite[i], kMiddleground);
    }
    unit_sprite = new Unit_Sprite*[100000];
    for (int i = 0; i < 100000; ++i) {
        unit_sprite[i] = new Unit_Sprite();
        unit_sprite[i] = Unit_Sprite::create();
    }
    building_sprite = new Building_Sprite*[1];
    for (int i = 0; i < 1; ++i) {
        building_sprite[i] = new Building_Sprite();
        building_sprite[i] = Building_Sprite::create();
    }
    
    
    vector<unit> temp = calculator->getVectorOfUnits(vectOfPlanets, vectOfRibs, 4);
    int id = 0;
    while(!temp.empty()){
        unit temp_unit = temp.back();
        unit_sprite[id]->set_unit_sprite(&temp.back());
        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
        unit_sprite[id]->setPosition(Vec2(coords.x, coords.y));
        temp.pop_back();
        this->addChild(unit_sprite[id], kMiddleground);
        ++id;
    }

    
    vectOfRibs.push_back(rib(planet_array[0], planet_array[1], 4));
    vectOfRibs.push_back(rib(planet_array[0], planet_array[2], 4));
    vectOfRibs.push_back(rib(planet_array[1], planet_array[2], 4));

    
    //    int gg = 0;
//      calculator->createBuilding(vectOfPlanets[1], 1);
//    tempo = vectOfPlanets[1].getVectorOfBuildings();
//    building_sprite[gg]->set_building_sprite(&tempo[0]);
//      coordinate_X_Y coords = tempo[0].getCoordinate();
//      building_sprite[gg]->setPosition(Vec2(coords.x, coords.y));
//      this->addChild(building_sprite[gg], kForeground);


   
    this->scheduleUpdate();
    return true;
}


//delta позволяет  сгладить  движения объектов в loop'e
void HelloWorld::update(float delta){

    calculator->doStep(vectOfPlanets, vectOfRibs, vectorOfShells, 4);
    vector<unit> temp = calculator->getVectorOfUnits(vectOfPlanets, vectOfRibs, 4);
    int size = temp.size();
    int id = 0;
    while(!temp.empty()){
        unit temp_unit = temp.back();
        unit_sprite[id]->set_unit_sprite(&temp.back());
        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
        unit_sprite[id]->setPosition(Vec2(coords.x, coords.y));
        temp.pop_back();
        ++id;
    }

    
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

void HelloWorld::set_max_unit_index(int num){
    max  = num;
}

