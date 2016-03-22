#include "GameLayer.h"

USING_NS_CC;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::createScene();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    _player1Score = 0;
    _player2Score = 0;
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    CCSprite * court = CCSprite::create("ship.png");
    court->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height
    * 0.5));
    this->addChild(court);
    _player1 = GameSprite::gameSpriteWithFile("planet.png");
    _player1->setPosition(ccp(_screenSize.width * 0.5, _player1->radius() * 2));
    this->addChild(_player1);
    _player2 = GameSprite::gameSpriteWithFile("planet.png");
    _player2->setPosition(ccp(_screenSize.width * 0.5, _screenSize.
    height - _player1->radius() * 2));
    this->addChild(_player2);


    _players = CCArray::create(_player1, _player2, NULL);
    _players->retain();

    _player1ScoreLabel = CCLabelTTF::create("0", "Arial", 60);
    _player1ScoreLabel->setPosition(ccp(_screenSize.width - 60, _screenSize.height * 0.5 - 80));
    _player1ScoreLabel->setRotation(90);
    this->addChild(_player1ScoreLabel);
    _player2ScoreLabel = CCLabelTTF::create("0", "Arial", 60);
    _player2ScoreLabel->setPosition(ccp(_screenSize.width - 60, _screenSize.height * 0.5 + 80));
    _player2ScoreLabel->setRotation(90);
    this->addChild(_player2ScoreLabel);
    this->setTouchEnabled(true);
    //create main loop
    this->schedule(schedule_selector(GameLayer::update));
    return true;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object



    // create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
   // menu->setPosition(Vec2::ZERO);
  //  this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void GameLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
