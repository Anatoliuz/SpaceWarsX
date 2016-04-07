//
//  Rocket_ThroughAppDelegate.cpp
//  Rocket Through
//
//  Created by Roger Engelbert on 11/17/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

/*
 
 Background music:
 8bit Dungeon Level by Kevin MacLeod (incompetech.com)
 
 */

#include "AppDelegate.h"

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(pEGLView);
    CCSize screenSize = pEGLView->getFrameSize();
    CCSize designSize = CCSize(768, 1024);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);
    
    
    float screenRatio = screenSize.height / screenSize.width;

    if (screenSize.width > 768) {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("ipadhd");
        pDirector->setContentScaleFactor(screenSize.height/designSize.height);
    } else if (screenSize.width > 320) {
        if (screenRatio >= 1.5f) {
            CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        } else {
            CCFileUtils::sharedFileUtils()->setResourceDirectory("ipad");
        }
        pDirector->setContentScaleFactor(screenSize.height/designSize.height);
    } else {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
        pDirector->setContentScaleFactor(screenSize.height/designSize.height);
    }
    
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("background.mp3"));
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("pickup.wav") );
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("bombRelease.wav") );
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("rocket.wav") );
    SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("shipBoom.wav") );
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.4f);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5f);
    

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
