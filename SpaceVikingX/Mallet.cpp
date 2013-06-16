//
//  Mallet.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "Mallet.h"
#include "Health.h"
Mallet::~Mallet(){
    CC_SAFE_DELETE( malletAnim);
}
bool Mallet::init(){
    bool bRet=true;
    if (bRet) {
        screenSize = CCDirector::sharedDirector()->getWinSize();
        gameObjectType = kPowerUpTypeMallet;
        this->initAnimations();
        this->changeState(kStateSpawning);
        
    }
    return bRet;
}

void Mallet::changeState(CharacterStates newState){
    if(newState == kStateSpawning){
        void* action = CCRepeatForever::create(CCAnimate::create(malletAnim));
        this->runAction((CCAction*)action);
    }else{
        this->setVisible(false);
        this->removeAllChildrenWithCleanup(true);
    }
    
}
void Mallet::updateStateWithDeltaTime(float dt, CCArray* listOfGameObjects){
    float groundHeight = screenSize.height*0.065f;
    if (this->getPosition().y>groundHeight) {
        this->setPosition(ccp(this->getPosition().x,this->getPosition().y-5.0f));
    }
}
void Mallet::initAnimations(){
    this->setMalletAnim(this->loadPlistForAnimationWithName("malletAnim", typeid(this).name()));
}
 Mallet*  Mallet:: createWithSpriteFrameName(const char *pszSpriteFrameName){
     CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
     
     char msg[256] = {0};
     sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
     CCAssert(pFrame != NULL, msg);
     
     Mallet *pobSprite = new Mallet();
     pobSprite->init();
     if (pobSprite && pobSprite->initWithSpriteFrame(pFrame))
     {
         pobSprite->autorelease();
         return pobSprite;
     }
     
     return NULL;
    
}