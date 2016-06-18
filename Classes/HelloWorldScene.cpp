#include "HelloWorldScene.h"

USING_NS_CC;


HelloWorld * HelloWorld::layer = nullptr;
Player_Info player_info;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    set_background();
    
    my_client = new client<calcModAdapter, Network>();
    my_controller = my_client->getContoller();
    

  

    set_planets();


    manage_units();
    player_info.player_num = my_controller->playerNum;
    
  
    vectOfRibs.push_back(rib(vectOfPlanets[0], vectOfPlanets[1], 4));
    vectOfRibs.push_back(rib(vectOfPlanets[0], vectOfPlanets[2], 4));
    vectOfRibs.push_back(rib(vectOfPlanets[1], vectOfPlanets[2], 4));

    // в calcModAdapter вызывыается doStep, который вызывает doStep олега, т.к doStep олега нужны планеты и ребра, то указатель нан их есть в calcModAdapter, но т.к они создаюстя тут, причем создаются вперемешку со спрайтами(т.е отделить в функцию и вынести не варик), тут будет создана структура dataModel и послана в calcModAdapter
    dataModel* data = new dataModel(4, player_info.player_num); // кол-во игроков 4 и номер клиента
    data->planets = &vectOfPlanets;
    data->ribs = &vectOfRibs;
    data->shells = &vectorOfShells;
    my_client->calculationMod->setData(data);
    //draw_shells();
    // вот и конец этому ужасу
    this->scheduleUpdate();
    return true;
}


//delta позволяет  сгладить  движения объектов в loop'e
void HelloWorld::update(float delta)
{
    while (this->getChildByTag(kUnit)) {
        this->removeChildByTag(kUnit);
    }
    while (this->getChildByTag(kShell)) {
        this->removeChildByTag(kShell);
    }

    
    manage_planets();
    draw_buildings_on_planet();        
    my_client->doWork();
    manage_units();

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


void HelloWorld::set_max_unit_index(int num){
    max  = num;
}

HelloWorld* HelloWorld::get_instance(){
    return layer;
}

Planet_Sprite* HelloWorld::get_planet_sprite_by_id(int num_of_planet ){
    for (auto it = planet_sprite.begin(); it < planet_sprite.end(); ++it) {
        
        if ((*it)->get_planet()->getNumberOfPlanet() == num_of_planet) {
            return *it;
        }
        
    }
}
void HelloWorld::manage_planets(){
    
    
    for (auto it = planet_sprite.begin(); it < planet_sprite.end(); ++it) {

        if( (*it)->is_touched() ) {

            if((*it)->get_planet()->getOwner() == player_info.player_num){
                
                auto button = ui::Button::create("hammer.png", "hammer.png", "hammer.png");
                player_info.planetId1 = (*it)->get_planet()->getNumberOfPlanet();
                player_info.is_touched = true;

                button->Node::setPosition(0,0);
                button->cocos2d::Node::setScale(0.7);
                (*it)->addChild(button, 4, 100);
                button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
                    switch (type)
                    {
                        case ui::Widget::TouchEventType::BEGAN:
                            my_controller->setCommand(player_info.planetId1, -1, 1);
                            player_info.planetId1 = -1;
                            (*it)->set_touch(false);
                            (*it)->removeAllChildren();
                            player_info.is_touched = false;

                            if (!(*it)->is_touched()) {
                                my_controller->setCommand((*it)->get_planet()->getNumberOfPlanet(), 0, 1);
                                // 0 - любое число, 1 - тип действия, тут 1 - постройка, 1 ый параметр номер планеты где строится
                                /*
                                my_client->calculationMod->createBuilding((*it)->get_planet()->
                                                                          getNumberOfPlanet(), player_info.player_num );//!!!!Не создает здание
                                */

                                
                            }
                            break;
                        case ui::Widget::TouchEventType::ENDED:
                            break;
                        default:
                            break;
                    }
                });
           
    
                
                
            }
            
            else {
           
                if( player_info.planetId1 >= 0 ) {
                    
                
                    
                    if(player_info.planetId2>= 0){
                    
                        auto button = ui::Button::create("attack.png", "attack.png", "attack.png");
                        button->Node::setPosition(0,0);
                        button->cocos2d::Node::setScale(0.7);
                        (*it)->addChild(button,6);
                  
                        button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
                        switch (type)
                        {
                            case ui::Widget::TouchEventType::BEGAN:
                                my_controller->setCommand(player_info.planetId1, player_info.planetId2, 2);
                                player_info.planetId1 = -1;
                                player_info.planetId2 = -1;
                                (*it)->removeAllChildren();
                                
                                break;
                            case ui::Widget::TouchEventType::ENDED:
                                
                                break;
                            default:
                                break;
                        }
                    });
                    
                    }
                }
            }
        }
    }
}
void HelloWorld::manage_units(){
    vector<unit> temp = my_client->getVectorOfUnits(vectOfPlanets, vectOfRibs, 4);
     int   num_of_units = temp.size();
    unit_sprite.resize(num_of_units);
    for (int i = 0; i < num_of_units; ++i) {
        unit_sprite[i] = new Unit_Sprite();
    }
    
    int id = 0;
    while(!temp.empty()){
        unit temp_unit = temp.back();
        int owner = temp_unit.get_owner_num();
        unit_sprite[id] = Unit_Sprite::create(owner);
        unit_sprite[id]->set_unit_sprite(&temp.back());
        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
        unit_sprite[id]->setPosition(Vec2(coords.x, coords.y));
        temp.pop_back();
        this->addChild(unit_sprite[id], kMiddleground, kUnit);
        ++id;
    }

    
}
void HelloWorld::set_planets(){
    
    
    vectOfPlanets.push_back(planet(0, 200, 300, 4));
    vectOfPlanets.push_back(planet(1, 700, 300, 4));
    vectOfPlanets.push_back(planet(2, 1200, 300, 4));
    vectOfPlanets.push_back(planet(3, 1200, 500, 4));

    num_of_planets = vectOfPlanets.size();
    vectOfPlanets[0].setOwner(0);
    vectOfPlanets[1].setOwner(0);
    vectOfPlanets[2].setOwner(1);
    vectOfPlanets[3].setOwner(1);
    planet_sprite.resize(num_of_planets);
    for (int i = 0; i < num_of_planets; ++i) {
        planet_sprite[i] = new Planet_Sprite();
        planet_sprite[i] = Planet_Sprite::create();
    }

    for (int i = 0; i < num_of_planets; ++i) {
        planet_sprite[i]->set_planet(&vectOfPlanets[i]);
        coordinate_X_Y coords = vectOfPlanets[i].getCoordinates();
        planet_sprite[i]->setPosition(coords.x, coords.y);
        this->addChild(planet_sprite[i], kMiddleground);
    }
}
void HelloWorld::draw_shells(){
//    vector<unit> temp = my_client->getVectorOfUnits(vectOfPlanets, vectOfRibs, 4);
//    num_of_units = temp.size();
//    unit_sprite.resize(num_of_units);
//    for (int i = 0; i < num_of_units; ++i) {
//        unit_sprite[i] = new Unit_Sprite();
//    }
//    int id = 0;
//    while(!temp.empty()){
//        unit temp_unit = temp.back();
//        int owner = temp_unit.get_owner_num();
//        unit_sprite[id] = Unit_Sprite::create(owner);
//        unit_sprite[id]->set_unit_sprite(&temp.back());
//        coordinate_X_Y coords = temp_unit.get_unit_coordinates();
//        unit_sprite[id]->setPosition(Vec2(coords.x, coords.y));
//        temp.pop_back();
//        this->addChild(unit_sprite[id], kMiddleground, kUnit);
//        ++id;
//    }
    auto node = DrawNode::create();
    node->drawLine(Vec2(200, 200), Vec2(200, 500), Color4F(1.0, 1.0, 1.0, 1.0));
    this->addChild(node);
}
void HelloWorld::set_background(){

    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size screenSize = CCDirector::sharedDirector()->getWinSize();
    Point center = Point(screenSize.width/2 + origin.x, screenSize.height/2 + origin.y);
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);
    
    auto label = Label::createWithTTF("SpaceWarsX", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    this->addChild(label, 1);
    
    
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("untitled.tmx");
    _background = _tileMap->layerNamed("Background");
    
   // this->addChild(_tileMap);
}

void HelloWorld::draw_buildings_on_planet(){
    for (auto i = 0; i < vectOfPlanets.size(); ++i){
    
    vector<building> temp = vectOfPlanets[i].getVectorOfBuildings();
    int num_of_buildings = temp.size();
    building_sprite.resize(num_of_buildings);
    for (int i = 0; i < num_of_buildings; ++i) {
        building_sprite[i] = new Building_Sprite();
        building_sprite[i] = Building_Sprite::create();
    }
    int id = 0;
    while(!temp.empty()){
        building temp_unit = temp.back();
        building_sprite[id]->set_building_sprite(&temp.back());
        coordinate_X_Y coords = temp_unit.getCoordinate();
        building_sprite[id]->setPosition(Vec2(coords.x, coords.y));
        temp.pop_back();
        this->addChild(building_sprite[id], kMiddleground, kBuilding);
        ++id;
    }
    }
}