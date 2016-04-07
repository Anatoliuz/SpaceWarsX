#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__


#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "planet.h"


USING_NS_CC;
using namespace CocosDenshion;

enum {
    kBackground,
    kMiddleground,
    kForeground
};

enum {
    kSpriteRocket,
    kSpritePlanet,
    kSpriteBoost,
    kSpriteStar
};

typedef enum gamestates {
    kGameIntro,
    kGamePaused,
    kGamePlay,
    kGameOver
    
}GameState;

class Rocket;
class LineContainer;
class GameSprite;
class planet;

class GameLayer : public CCLayer {
    
	planet *_planet;
    Rocket * _rocket;
    LineContainer * _lineContainer;
    
    CCSpriteBatchNode *_gameBatchNode;
    CCLabelBMFont * _scoreDisplay;
    
    GameSprite * _pauseBtn;
    CCSprite * _intro;
    CCSprite *_gameOver;
    CCSprite *_paused;
    
    CCParticleSystem * _star;
    CCParticleSystem * _jet;
    CCParticleSystem * _boom;
    CCParticleSystem * _comet;
    CCParticleSystem * _pickup;
    CCParticleSystem * _warp;
    
    CCArray * _planets;
    CCSize _screenSize;
    
    GameState _state;
    
    bool _drawing;
    bool _running;

    std::vector<CCPoint> _grid;
    int _gridIndex;
    
    int _minLineLength;
    float _cometInterval;
    float _cometTimer;
    
    void resetGame(void);
    void resetStar(void);
    void killPlayer(void);
    
    void createGameScreen(void);
    void createParticles(void);
    void createStarGrid(void);

	int _score;
	float _timeBetweenPickups;
    
public:
    ~GameLayer(void);
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void update (float dt);
	
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
	

};

#endif // __GAMELAYER_H__
