//
//  SpaceCargoShip.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "SpaceCargoShip.h"
void SpaceCargoShip:: dropCargo() {
    CCPoint cargoDropPosition = ccp(screenSize.width/2, screenSize.height);
    if (hasDroppedMallet == false) {
        CCLOG("SpaceCargoShip --> Mallet Powerup was created!");
        hasDroppedMallet = true;
        delegate->createObjectOfType(kPowerUpTypeMallet, 0.0f, cargoDropPosition, 50);
       
    } else {
        CCLOG("SpaceCargoShip --> Health Powerup was created!");
          delegate->createObjectOfType(kPowerUpTypeHealth, 0.0f, cargoDropPosition, 50);
       
    }
}

bool SpaceCargoShip:: init()
{
    bool bRet=GameObject::create();
    if( (bRet) )
    {
        CCLOG("SpaceCargoShip init");
        hasDroppedMallet = false;
        
        float shipHeight = screenSize.height * 0.71f;
        CCPoint position1 = ccp(screenSize.width * -0.48f, shipHeight);
        CCPoint position2 = ccp(screenSize.width * 2.0f, shipHeight);
        CCPoint position3 = ccp(position2.x * -1.0f, shipHeight);
        CCPoint offScreen = ccp(screenSize.width * -1.0f,
                                screenSize.height * -1.0f);
        void* action=CCRepeatForever::create(CCSequence::create(CCDelayTime::create(2.0f),CCMoveTo::create(0.01f, position1),CCScaleTo::create(0.01, 0.5),CCFlipX::create(true),CCMoveTo::create(8.5, position2),CCScaleTo::create(0.1, 1.0),CCFlipX::create(false),CCMoveTo::create(7.5, position3),CCScaleTo::create(0.1, 2.0),CCFlipX::create(true),CCScaleTo::create(0.1, 4.0),CCMoveTo::create(4.5, position2),CCCallFunc::create(this, callfunc_selector(SpaceCargoShip::dropCargo)),CCMoveTo::create(0.0, offScreen),NULL));

      
        this->runAction((CCAction*)action);
        
    }
    return bRet;
}

SpaceCargoShip* SpaceCargoShip::createWithSpriteFrameName(const char *pszSpriteFrameName){
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
    
    SpaceCargoShip *pobSprite = new SpaceCargoShip();
    pobSprite->init();
    if (pobSprite && pobSprite->initWithSpriteFrame(pFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    //    CC_SAFE_DELETE(pobSprite);
    return NULL;
    
}