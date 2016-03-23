#include "GameLayer.h"

USING_NS_CC;

Scene* GameLayer::scene()
{
    auto scene = Scene::create();

    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance

void GameLayer::update(float dt){

  }



// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
     // 1. super init first
     if ( !Layer::init() )
     {
         return false;
     }

     auto visibleSize = Director::getInstance()->getVisibleSize();
     auto origin = Director::getInstance()->getVisibleOrigin();

     /////////////////////////////
     // 2. add a menu item with "X" image, which is clicked to quit the program
     //    you may modify it.

     // add a "close" icon to exit the progress. it's an autorelease object
     auto closeItem = MenuItemImage::create(
                                         "CloseNormal.png",
                                         "CloseSelected.png",
                                         CC_CALLBACK_1(GameLayer::menuCloseCallback,this));

     closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

     // create menu, it's an autorelease object
     auto menu = Menu::create(closeItem, nullptr);
     menu->setPosition(Vec2::ZERO);
     this->addChild(menu, 1);

     /////////////////////////////
     // 3. add your codes below...

     // add a label shows "Hello World"
     // create and initialize a label

    // auto label = Label::createWithTTF("Hello World", "fonts/arial.ttf", TITLE_FONT_SIZE);

     // position the label on the center of the screen
    // label->setPosition(origin.x + visibleSize.width/2,

     // add the label as a child to this layer
    // this->addChild(label, 1);

     // add "HelloWorld" splash screen"
    // auto sprite = Sprite::create("space.png");

     // position the sprite on the center of the screen
   //  sprite->setPosition(Vec2(visibleSize / 2) + origin);

     // add the sprite as a child to this layer
    // this->addChild(sprite);

     screenSize = CCDirector::sharedDirector()->getWinSize();
CCSprite * court = CCSprite::create("space.png");
court->setPosition(ccp(screenSize.width * 0.5, screenSize.height*0.5) );
this -> addChild(court);

player1 = GameSprite::gameSpriteWithFile("rocket.png");
player1->setPosition(ccp(screenSize.width * 0.5, player1->radius() * 2));
player1->setScale(0.5);
this->addChild(player1);
player2 = GameSprite::gameSpriteWithFile("rocket.png");
player2->setPosition(ccp(screenSize.width * 0.5, screenSize.height - player1->radius() * 2));
player2->setScale(0.5);

this->addChild(player2);

ball = GameSprite::gameSpriteWithFile("rocket.png");
ball->setPosition(ccp(screenSize.width * 0.5, screenSize.height * 0.5 -2 *  ball->radius() * 2));

this->addChild(ball);
players = CCArray::create(player1, player2, NULL);
players->retain();


//this->setTouchEnabled(true);
//this->schedule(schedule_selector(GameLayer::update));
     return true;


}



//void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
//CCSetIterator i;
//CCTouch* touch;
//CCPoint tap;
//GameSprite * player;
//for( i = pTouches->begin(); i != pTouches->end(); i++) {
//touch = (CCTouch*) (*i);
//if(touch) {
//tap = touch->getLocation();
//for (int p = 0; p < 2; p++) {
//player = (GameSprite *) players->objectAtIndex(p);
//if (player->boundingBox().containsPoint(tap)) {
//player->setTouch(touch);
//}
//}
//}
//}
//}

//void GameLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
//    for (int p = 0; p < _players->count(); p++) {
//    player = (GameSprite *) _players->objectAtIndex(p);
//    if (player->getTouch() != NULL && player->getTouch() ==
//    touch) {
//        CCPoint nextPosition = tap;
//        //keep player inside screen
//        if (nextPosition.x < player->radius())
//        nextPosition.x = player->radius();
//        if (nextPosition.x > _screenSize.width - player-
//        >radius())
//        nextPosition.x = _screenSize.width - player-
//        >radius();
//        if (nextPosition.y < player->radius())
//        nextPosition.y = player->radius();
//        if (nextPosition.y > _screenSize.height - player-
//        >radius())
//        nextPosition.y = _screenSize.height - player->radius();
//        //keep player inside its court
//        if (player->getPositionY() < _screenSize.height *
//        0.5f)
//        {
//        if (nextPosition.y >
//        _screenSize.height * 0.5 - player->radius())
//        {
//        nextPosition.y =
//        _screenSize.height * 0.5 - player-
//        >radius();
//        }
//        } else {
//        if (nextPosition.y <
//        _screenSize.height * 0.5 + player->radius())
//        {
//        nextPosition.y =
//        _screenSize.height * 0.5 + player-
//        >radius();
//        }
//        }
//        player->setNextPosition(nextPosition);
//        player->setVector(ccp(tap.x - player->getPositionX(),
//        tap.y - player->getPositionY()));
//        }
//        }

//}
//void GameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event){
//    for (int p = 0; p < _players->count(); p++) {
//    player = (GameSprite *) _players->objectAtIndex(p);
//    if (player->getTouch() != NULL && player->getTouch() ==
//    touch) {
//    player->setTouch(NULL);
//    player->setVector(ccp(0,0)););
//    }
//    }
//}


GameLayer::~GameLayer(){
    CC_SAFE_RELEASE(players);
}


void GameLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
