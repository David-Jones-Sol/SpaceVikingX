//
//  GameScene.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "GameScene.h"
bool GameScene::init(){
    bool bRet = false;
    bRet = CCScene::init();
	if ( bRet )
	{
      
        BackgroundLayer *backgroundLayer=BackgroundLayer::create();
        
        this->addChild(backgroundLayer,0);
        GameplayLayer *gameplayLayer =GameplayLayer::create();
        this->addChild(gameplayLayer, 5);
    }
    return true;
}