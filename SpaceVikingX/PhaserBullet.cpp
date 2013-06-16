//
//  PhaserBullet.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "PhaserBullet.h"
PhaserBullet::~PhaserBullet(){
    CC_SAFE_DELETE(firingAnim);
    CC_SAFE_DELETE(travelingAnim);
}
void PhaserBullet::changeState(CharacterStates newState){
    this->stopAllActions();
    void *action = NULL;
    this->setCharacterState(newState);
    
    switch (newState) {
        case kStateSpawning:
            CCLOG("Phaser->Changed state to Spawning");
            action =CCAnimate::create(firingAnim);
            break;
            
        case kStateTraveling:
        {
            CCLOG("Phaser->Changed state to Traveling");
            action = CCAnimate::create(travelingAnim);
            CCPoint endLocation;
            if (myDirection == kDirectionLeft) {
                CCLOG("Phaser direction LEFT");
                endLocation = ccp(-10.0f,this->getPosition().y);
            } else {
                CCLOG("Phaser direction RIGHT");
                endLocation = ccp(screenSize.width+24.0f,this->getPosition().y);
            }
            this->runAction(CCMoveTo::create(2, endLocation));
            action = CCRepeatForever::create(CCAnimate::create(travelingAnim));
        }
            break;
          case kStateDead:
            CCLOG("Phaser->Changed state to dead");
            // Remove from parent
            this->setVisible(false);
            this->removeFromParentAndCleanup(true);
        default:
            break;
  
    }
    if (action != NULL) {
        this->runAction((CCAction*)action);
    }

}
bool PhaserBullet::isOutsideOfScreen(){
    CCPoint currentSpritePosition = this->getPosition();
    if (currentSpritePosition.x<0.0f||currentSpritePosition.x>screenSize.width) {
        this->changeState(kStateDead);
    }
    return false;
}
void PhaserBullet:: updateStateWithDeltaTime(float deltaTime,CCArray* listOfGameObjects)
{
    if (this->isOutsideOfScreen()) {
        return;
    }
    if (this->numberOfRunningActions()==0) {
        if (characterState ==kStateSpawning) {
            this->changeState(kStateTraveling);
            return;
        }else{
            this->changeState(kStateDead);
            return;
        }
    }
}

void PhaserBullet:: initAnimations(){
    this->setFiringAnim(this->loadPlistForAnimationWithName("firingAnim", typeid(this).name()));
}
bool PhaserBullet:: init(){
    bool bRet = GameCharacter::init();
    if (bRet) {
        CCLOG("### PhaserBullet initialized");
        this->initAnimations();
        gameObjectType = kEnemyTypePhaser;
    }
    return bRet;
}
