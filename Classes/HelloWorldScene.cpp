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
    vectOfRibs.push_back(rib(vectOfPlanets[0], vectOfPlanets[3], 4));

    vectOfRibs.push_back(rib(vectOfPlanets[1], vectOfPlanets[3], 4));
    vectOfRibs.push_back(rib(vectOfPlanets[1], vectOfPlanets[4], 4));
    vectOfRibs.push_back(rib(vectOfPlanets[2], vectOfPlanets[5], 4));
    
    vectOfRibs.push_back(rib(vectOfPlanets[3], vectOfPlanets[4], 4));
    vectOfRibs.push_back(rib(vectOfPlanets[3], vectOfPlanets[5], 4));
    vectOfRibs.push_back(rib(vectOfPlanets[4], vectOfPlanets[5], 4));
    
    // в calcModAdapter вызывыается doStep, который вызывает doStep олега, т.к doStep олега нужны планеты и ребра, то указатель нан их есть в calcModAdapter, но т.к они создаюстя тут, причем создаются вперемешку со спрайтами(т.е отделить в функцию и вынести не варик), тут будет создана структура dataModel и послана в calcModAdapter
    dataModel* data = new dataModel(4, player_info.player_num); // кол-во игроков 4 и номер клиента
    data->planets = &vectOfPlanets;
    data->ribs = &vectOfRibs;
    data->shells = &vectorOfShells;
    my_client->calculationMod->setData(data);
    //draw_shells();
    draw_ribs();
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
    while (this->getChildByTag(kBuilding)) {
        this->removeChildByTag(kBuilding);

    }
    
    manage_planets();
    draw_buildings_on_planet();        
    my_client->doWork();
    manage_units();
    draw_shells();
}
void HelloWorld::clear_buttons(Planet_Sprite *temp){
    while(temp->getChildByTag(kButton))
        temp->removeChildByTag(kButton);
    temp->set_touch(false);
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
    if((*it)->is_touched()){
        if( ( (*it)->get_planet()->getOwner() == player_info.player_num || (*it)->get_planet()->getUnitsCount(player_info.player_num) > 0 )
           && player_info.planetId1 < 0
                ){
            
            player_info.planetId1 = (*it)->get_planet()->getNumberOfPlanet();
            auto button = ui::Button::create("hammer.png", "hammer.png", "hammer.png");
            player_info.planetId1 = (*it)->get_planet()->getNumberOfPlanet();
            button->Node::setPosition(0,0);
            button->cocos2d::Node::setScale(0.7);
            (*it)->addChild(button, kForeground, kButton);
            (*it)->set_touch(false);

            button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
                switch (type)
                {
                    case ui::Widget::TouchEventType::BEGAN:
                        if  (player_info.planetId2 >= 0){
                            clear_buttons(get_planet_sprite_by_id(player_info.planetId2));
                            
                        }
                        my_controller -> setCreateBuilding(playe_info.planetId1); // контролер знает id игрока, нет нужды передавать
                       /* my_controller->setCommand(player_info.planetId1, -1, 1); */
                        clear_buttons(get_planet_sprite_by_id(player_info.planetId1));

                        player_info.planetId1 = -1;
                        // 0 - любое число, 1 - тип действия, тут 1 - постройка, 1 ый параметр номер планеты где строится
                        /*
                         my_client->calculationMod->createBuilding((*it)->get_planet()->
                         getNumberOfPlanet(), player_info.player_num );//!!!!Не создает здание
                         */
                        break;
                    case ui::Widget::TouchEventType::ENDED:
                        break;
                    default:
                        break;
                }
            });
        }
        else {
            if (player_info.planetId1 < 0) {
                player_info.planetId1 = (*it)->get_planet()->getNumberOfPlanet();
            }
            else {
                if (!(*it)->getChildByTag(kButton)) {
                
                player_info.planetId2 = (*it)->get_planet()->getNumberOfPlanet();
                auto button = ui::Button::create("attack.png", "attack.png", "attack.png");
                button->Node::setPosition(0,0);
                button->cocos2d::Node::setScale(0.7);
                (*it)->addChild(button, 100, kButton);
                
                button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type){
                    switch (type)
                    {
                        case ui::Widget::TouchEventType::BEGAN:
                            my_comntroller -> setMove(player_info.planetId1, playe_info.planetId2, 1); // 1 - количество пересылаемых кораблей если есть откуда их получить то передай переменную.

/*                            my_controller->setCommand(player_info.planetId1, player_info.planetId2, 2); */
                            clear_buttons(get_planet_sprite_by_id(player_info.planetId1));
                            clear_buttons(get_planet_sprite_by_id(player_info.planetId2));
                            
                            player_info.planetId1 = -1;
                            player_info.planetId2 = -1;
                    
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
    
    vectOfPlanets.push_back(planet(0, 200, 550, 4));
    vectOfPlanets.push_back(planet(1, 300, 200, 4));
    vectOfPlanets.push_back(planet(2, 700, 750, 4));
    vectOfPlanets.push_back(planet(3, 700, 400, 4));
    vectOfPlanets.push_back(planet(4, 1100, 200, 4));
    vectOfPlanets.push_back(planet(5, 1200, 550, 4));
    num_of_planets = vectOfPlanets.size();
    vectOfPlanets[0].setOwner(0);
    vectOfPlanets[5].setOwner(1);
    
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

    for (auto i = 0; i < vectorOfShells.size(); ++i){
        coordinate_X_Y temp_start = vectorOfShells[i].get_start();
        coordinate_X_Y temp_finish = vectorOfShells[i].get_finish();
        auto node = DrawNode::create();
        node->drawLine(Vec2(temp_start.x, temp_start.y), Vec2(temp_finish.x, temp_finish.y), Color4F(1.0, 1.0, 1.0, 1.0));
        this->addChild(node, kForeground, kShell);
    }
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
    
    this->addChild(_tileMap);
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

void HelloWorld::draw_ribs(){
    for (int i = 0; i < vectOfRibs.size(); ++i) {
       coordinate_X_Y start =  vectOfPlanets[vectOfRibs[i].getNumb1() ].getCoordinates();
       coordinate_X_Y  finish  = vectOfPlanets[vectOfRibs[i].getNumb2() ].getCoordinates();
        Color3B clr = Color3B::MAGENTA;
        Color4F clrb = Color4F(clr);
        DrawNode *ln = DrawNode::create();
        float lineWidth = 0.04 * CC_CONTENT_SCALE_FACTOR();
        auto node = DrawNode::create();
        node->drawSegment(Vec2(start.x, start.y), Vec2(finish.x, finish.y), lineWidth,clrb);
            this->addChild(node, kForeground, kRibs);

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
