//
//  BackgroundLayer.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "BackgroundLayer.h"
bool BackgroundLayer::init(){
    bool bRet = false;
    bRet = CCLayer::init();
	if ( bRet )
	{
        
        CCSprite* backgroundImage = CCSprite::create("backgroundiPhone.png");
        
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        backgroundImage->setPosition(
                                     ccp(screenSize.width/2, screenSize.height/2));
        this->addChild(backgroundImage,0,0);
    }
    return bRet;
}