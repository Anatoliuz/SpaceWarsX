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

    //unit_sprite = Unit_Sprite::create();
    building_sprite = Building_Sprite::create();
  //  planet_sprite = Planet_Sprite::create();
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
    vector<unit> temp = calculator->getVectorOfUnits(vectOfPlanets, vectOfRibs, 4);
    int size = temp.size();
    
    int id = 0;
    while(!temp.empty()){
        
        unit temp_unit = temp.back();
        //int id =  temp_unit.get_id();
        //id -= num_of_units;
        unit_sprite[id]->set_unit_sprite(&temp.back());
        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
        unit_sprite[id]->setPosition(Vec2(coords.x, coords.y));
        temp.pop_back();
        this->addChild(unit_sprite[id], kMiddleground);
        ++id;
    }
//    for (int k = 0; k < num_of_planetss; ++k) {
//       planet_sector = planet_array[k].getMassOfSectors();
//        for (int i = 0; i < 5; ++i) {
//            for (int j = 0; j < 8; ++j) {
//             list_units = planet_sector[i][j].getMassOfPlayersLists();
//                for(int jndex = 0; jndex < num_of_playerss; ++jndex){
//                    while (!list_units[jndex].empty()) {
//                        unit temp_unit =  list_units[jndex].front();
//                        int id =  temp_unit.get_id();
//                        id -= num_of_units;
//                        unit_sprite[id]->set_unit_sprite(&list_units[jndex].front());
//                        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
//                        unit_sprite[id]->setPosition(Vec2(coords.x, coords.y));
//                        list_units[jndex].pop_front();
//                        this->addChild(unit_sprite[id], kMiddleground);
//                    }
//                }
//            }
//        }
//    }

    
    vectOfRibs.push_back(rib(planet_array[0], planet_array[1], 4));
    vectOfRibs.push_back(rib(planet_array[0], planet_array[2], 4));
    vectOfRibs.push_back(rib(planet_array[1], planet_array[2], 4));
    
    calculator->createBuilding(vectOfPlanets[0], 0);
    vector<building> tempo;
    
    for (auto it = vectOfRibs.begin(); it != vectOfRibs.end(); ++it) {
        
    }
//    while(!vectOfRibs.empty()){
//        rib temp = vectOfRibs.front();
//        list_units_ribs = temp.getMassOfPlayersLists();
//        while (!list_units_ribs->empty()) {
//            ribStruct* temp = &list_units_ribs->front();
//            unit_sprite[index_of_unit]->set_unit_sprite(&temp->oneUnit);
//            coordinate_X_Y coords = temp->oneUnit.get_unit_coordinates();
//            unit_sprite[index_of_unit]->setPosition(Vec2(coords.x, coords.y));
//            list_units_ribs->pop_front();
//            this->addChild(unit_sprite[index_of_unit], kMiddleground);
//            ++index_of_unit;
//        }
//    }
    //calculator->createBuilding(vectOfPlanets[1], 1);
  //  calculator->createBuilding(vectOfPlanets[2], 0);

//рисуем планеты
    for(int i = 0; i < num_of_planetss; ++i){
        //vectOfBuildings = vectOfPlanets[i].getVectorOfBuildings();
        
    }
//    std::cout << "\n";
   
    set_max_unit_index(num_of_units)    ;
    //this->toGameScene();

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
        //int id =  temp_unit.get_id();
        //id -= num_of_units;
        unit_sprite[id]->set_unit_sprite(&temp.back());
        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
        unit_sprite[id]->setPosition(Vec2(coords.x, coords.y));
        temp.pop_back();
       // this->addChild(unit_sprite[id], kMiddleground);
        ++id;
    }
    
//    int max = id;
//    for (int i =0 ; i < max; ++i) {
//        this->removeChild(unit_sprite[i], kMiddleground);
//    }
//    for(int k = 0; k < num_of_planetss; ++k){
//        planet_sector = vectOfPlanets[k].getMassOfSectors();
//        for(int i = 0; i < 5; ++i){
//            for(int j = 0; j < 8; ++j){
//                list_units = planet_sector[i][j].getMassOfPlayersLists();
//                for(int jndex = 0; jndex < num_of_playerss; ++jndex){
//                    while (!list_units[jndex].empty()) {
//                        unit temp_unit =  list_units[jndex].front();
//                        int id =  temp_unit.get_id();
//                        id -= num_of_units;
//                        unit_sprite[id]->set_unit_sprite(&list_units[jndex].front());
//                        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
//                    //    unit_sprite[id]->setPosition(Vec2(coords.x, coords.y));
//                        list_units[jndex].pop_front();
//                    }
//                }
//            }
//        }
//    }
    
    
    //calculator->doStep(vectOfPlanets, vectOfRibs, vectorOfShells, 4);
//    index_of_unit = 0;
//    planet_sector = planet_array[0].getMassOfSectors();
//            for (int j = 0; j < 8; ++j) {
//                list_units = planet_sector[0][j].getMassOfPlayersLists();
//                    while (!list_units[0].empty()) {
//                        unit_sprite[index_of_unit]->set_unit_sprite(&list_units[0].front());
//                        unit temp_unit =  list_units[0].front();
//                        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
//                        unit_sprite[index_of_unit]->setPosition(Vec2(coords.x, coords.y));
//                        list_units[0].pop_front();
//                         ++index_of_unit;
//                    }
//                }
    
}

//    for (int j = 0; j < 8; j++){
//        list_units_1 =  rockets_to_print[0][j].getListOfUnits1();
//        while(!list_units_1.empty()) {
//            unit temp_unit =  list_units_1.front();
//            coordinate_X_Y coords = temp_unit.get_unit_coordinates();
//            unit_sprite_1->setPosition(coords.x, coords.y);
//            list_units_1.pop_front();
//        }
//    }

    
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

void HelloWorld::transitionToGameScene()
{
    auto size = Director::getInstance()->getWinSize();      //get the windows size.
    
    auto clipper = ClippingNode::create();      // create the ClippingNode object
    
    auto stencil = DrawNode::create();      // create the DrawNode object which can draw dots, segments and polygons.
    
    Point triangle[3];      // init the  triangle vertexes. here my win size is 360x640, so my triangle vertexes init by these values. You can change the values to adapt your scree.
    triangle[0] = Point(-size.width * 1.5f, -size.height / 2);
    triangle[1] = Point(size.width * 1.5f, -size.height / 2);
    triangle[2] = Point(0, size.height);
    Color4F green(0, 1, 0, 1);
    
    stencil->drawPolygon(triangle, 3, green, 0, green);     //use the drawNode to draw the triangle to cut the ClippingNode.
    
    clipper->setAnchorPoint(Point(0.5f, 0.5f));     // set the ClippingNode anchorPoint, to make sure the drawNode at the center of ClippingNode
    clipper->setPosition(size.width / 2, size.height / 2);
    clipper->setStencil(stencil);   //set the cut triangle in the ClippingNode.
    clipper->setInverted(true);     //make sure the content is show right side.
    
    Sprite* blackRect = Sprite::create("black_screen.png");     //create a black screen sprite to make sure the bottom is black. the"black_screen.png" is a "black screen" png.
    
    clipper->addChild(blackRect);   //to make sure the cover is black.
    
    this->addChild(clipper, 500);
    
    // the Clipping node triangle  add some actions to make the triangle scale and rotate.
    stencil->runAction(EaseSineOut::create(Spawn::create(ScaleTo::create(2.5f, 0.0f, 0.0f), RotateBy::create(2.5f, 540),
                                                         Sequence::create(DelayTime::create(2.5), CallFunc::create(this, callfunc_selector(HelloWorld::toGameScene)), NULL), NULL)));
    
}

void HelloWorld::toGameScene()
{
    //get the game scene and run it.
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
}


