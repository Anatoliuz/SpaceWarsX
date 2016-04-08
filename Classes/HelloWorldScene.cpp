#include "HelloWorldScene.h"

USING_NS_CC;

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
    
    auto space = Sprite::create("space.png");
    space->setPosition(Vec2(screenSize.width/2, screenSize.height/2));
    this->addChild(space, kBackground);
    
    _planet = planet::create();
    coordinate_X_Y planet_coord = _planet->get_planet_coordinates();
    _planet->setPosition(Vec2(planet_coord.x,planet_coord.y));
    _planet->setScaleX(_planet->get_planet_radius()/_planet->getContentSize().width);
    _planet->setScaleY(_planet->get_planet_radius()/_planet->getContentSize().height);
    this->addChild(_planet, kMiddleground);
    this->scheduleUpdate();

//
   // coordinate_X_Y planet_coordinate = planet::get_planet_coordinates();
   // _planet->setPosition(planet_coordinate.x, planet_coordinate.y);
   // this->addChild(_mySprite, kMiddleground);

    return true;
}

void HelloWorld::update(float delta){
    auto position = _planet->getPosition();
    position.x -= 250 * delta;
    if (position.x  < 0 - (_planet->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + _planet->getBoundingBox().size.width/2;
    _planet->setPosition(position);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
