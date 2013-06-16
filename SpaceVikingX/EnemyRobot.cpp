//
//  EnemyRobot.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "EnemyRobot.h"
EnemyRobot::~EnemyRobot(){
    CC_SAFE_DELETE(robotWalkingAnim);
    CC_SAFE_DELETE(raisePhaserAnim);
    CC_SAFE_DELETE(shootPhaserAnim);
    CC_SAFE_DELETE(lowerPhaserAnim);
    CC_SAFE_DELETE(torsoHitAnim);
    CC_SAFE_DELETE(headHitAnim);
    CC_SAFE_DELETE(robotDeathAnim);
}
void EnemyRobot::shootPhaser(){
    CCPoint phaserFiringPosition;
    PhaserDirection phaserDir;
    CCRect boundingBox = this->boundingBox();
    CCPoint position = this->getPosition();
    
    float xPosition = position.x + boundingBox.size.width * 0.542f;
    float yPosition = position.y + boundingBox.size.height * 0.25f;
    
    if (this->isFlipX()) {
        CCLOG("Facing right, Firing to the right");
        phaserDir = kDirectionRight;
    } else {
        CCLOG("Facing left, Firing to the left");
        xPosition = xPosition * -1.0f; // Reverse direction
        phaserDir = kDirectionLeft;
    }
    phaserFiringPosition = ccp(xPosition, yPosition);
    delegate->createPhaseWithDirection(phaserDir, phaserFiringPosition);
   
}
CCRect EnemyRobot::eyesightBoundingBox(){
    // Eyesight is 3 robot widths in the direction the robot is facing.
    CCRect robotSightBoundingBox;
    CCRect robotBoundingBox = this->adjustedBoundingBox();
    if (this->isFlipX()) {
        robotSightBoundingBox = CCRectMake(robotBoundingBox.origin.x, robotBoundingBox.origin.y,  robotBoundingBox.size.width*3.0f, robotBoundingBox.size.height);
    } else {
        robotSightBoundingBox =
        CCRectMake(robotBoundingBox.origin.x -
                   (robotBoundingBox.size.width*2.0f),
                   robotBoundingBox.origin.y,
                   robotBoundingBox.size.width*3.0f,
                   robotBoundingBox.size.height);
    }
    return robotSightBoundingBox;
 
}



 void EnemyRobot:: changeState(CharacterStates newState) {
     if (characterState == kStateDead)
         return;  // No need to change state further once I am dead
     this->stopAllActions();
   
    void* action = NULL;
    characterState = newState;
    
    switch (newState) {
        case kStateSpawning:
            this->runAction(CCFadeOut::create(0.01f));
           
            // Fades out the sprite if it was visible before
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("teleport.png"));
            action =CCSpawn::create(CCRotateBy::create(1.5f,360),CCFadeIn::create(1.5f),NULL);
            break;
            
        case kStateIdle:
            CCLOG("EnemyRobot->Changing State to Idle");
             this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("an1_anim1"));
            
            break;
            
        case kStateWalking:
        {  CCLOG("EnemyRobot->Changing State to Walking");
            if (isVikingWithinBoundingBox)
                break; // AI will change to Attacking on next frame
            
            float xPositionOffSet = 150.0f;
            if (isVikingWithinSight) {
                if (vikingCharacter->getPosition().x < this->getPosition().x)
                    xPositionOffSet = xPositionOffSet * -1;
                    // Invert to -150
                    } else {
                        if (CCRANDOM_0_1() > 0.5f)
                            xPositionOffSet = xPositionOffSet * -1;
                            
                            if (xPositionOffSet > 0.0f) {
                                this->setFlipX(true);
                            } else {
                                this->setFlipX(false);
                            }
                    }
            action =CCSpawn::create(CCAnimate::create(robotWalkingAnim),CCMoveTo::create(2.4f, ccp(this->getPosition().x+xPositionOffSet,this->getPosition().y)),NULL);
    }
            break;
            
        case kStateAttacking:
        { CCLOG("EnemyRobot->Changing State to Attacking");
            action =CCSequence::create(CCAnimate::create(raisePhaserAnim),CCDelayTime::create(1.0f),CCAnimate::create(shootPhaserAnim),CCCallFunc::create(this, callfunc_selector(EnemyRobot:: shootPhaser)),CCAnimate::create(lowerPhaserAnim),CCDelayTime::create(2.0f),NULL);
        }
            break;
            
        case kStateTakingDamage:
            CCLOG("EnemyRobot->Changing State to TakingDamage");
            if (vikingCharacter->getWeaponDamage() > kVikingFistDamage){
                // If the viking has the mallet, then
                action =CCAnimate::create(headHitAnim);
              
            } else {
                // Viking does not have weapon, body blow
                action =CCAnimate::create(torsoHitAnim);
                
            }
            break;
            
        case kStateDead:
            CCLOG("EnemyRobot -> Going to Dead State");
            action =CCSequence::create(CCAnimate::create(robotDeathAnim),CCDelayTime::create(2.0f),CCFadeOut::create(2.0f),NULL);

            break;
            
        default:
            CCLOG("Enemy Robot -> Unknown CharState %d",
                  characterState);
            break;
    }
    
    if (action != NULL)
        this->runAction((CCAction*)action);
}
void EnemyRobot:: updateStateWithDeltaTime(float deltaTime, CCArray *listOfGameObjects) {
    this->checkAndClampSpritePosition();
    
    if ((characterState != kStateDead) && (characterHealth <= 0)) {
        this->changeState(kStateDead);
        return;
    }
    
    vikingCharacter =
    (GameCharacter*)this->getParent()->getChildByTag(kVikingSpriteTagValue);

    CCRect vikingBoudingBox = vikingCharacter->adjustedBoundingBox(); 
    CCRect robotBoundingBox = this->adjustedBoundingBox();
    CCRect robotSightBoundingBox = this->eyesightBoundingBox();    isVikingWithinBoundingBox =vikingBoudingBox.intersectsRect(robotBoundingBox)?true:false;
    
    isVikingWithinSight =vikingBoudingBox.intersectsRect(robotSightBoundingBox)?true:false;
 
    
    if ((isVikingWithinBoundingBox) &&
        (vikingCharacter->getCharacterState() == kStateAttacking)) {
        // Viking is attacking this robot
        if ((characterState != kStateTakingDamage) &&
            (characterState != kStateDead)) {
            this->setCharacterHealth(this->getCharacterHealth()-vikingCharacter->getWeaponDamage());
           
            if (characterHealth > 0) {
                this->changeState(kStateTakingDamage);

            } else {
                 this->changeState(kStateDead);
                
            }
            return; // Nothing to update further, stop and show damage
        }
    }
    
    if (this->numberOfRunningActions()== 0) {
        
        if (characterState == kStateDead) {
            // Robot is dead, remove
            this->setVisible(false);
            this->removeAllChildrenWithCleanup(true);
           
        } else if (vikingCharacter->getCharacterState()  == kStateDead) {
            // Viking is dead, walk around the scene
            this->changeState(kStateWalking);

        } else if (isVikingWithinSight) {
             this->changeState(kStateAttacking);
        
        }  else {
            // Viking alive and out of sight, resume walking
             this->changeState(kStateWalking);  
        }
    }
}
CCRect EnemyRobot:: AdjustedBoundingBox() {
    // Shrink the bounding box by 18% on the X axis, and move it to the right by 18%
    // and crop it by 5% on the Y Axis.
    // On the iPad this is 30 pixels on the X axis and cut 10 pixels from the top
    CCRect enemyRobotBoudingBox = this->boundingBox();
    float xOffsetAmount = enemyRobotBoudingBox.size.width * 0.18f;
    float yCropAmount = enemyRobotBoudingBox.size.height * 0.05f;
    enemyRobotBoudingBox = CCRectMake(enemyRobotBoudingBox.origin.x + xOffsetAmount,
                                      enemyRobotBoudingBox.origin.y,
                                      enemyRobotBoudingBox.size.width - xOffsetAmount,
                                      enemyRobotBoudingBox.size.height - yCropAmount);
    return enemyRobotBoudingBox;
}

#pragma mark -
#pragma mark initAnimations
void EnemyRobot:: initAnimations() {
    this->setLowerPhaserAnim(this->loadPlistForAnimationWithName("robotWalkingAnim", typeid(this).name()));
    this->setLowerPhaserAnim(this->loadPlistForAnimationWithName("raisePhaserAnim", typeid(this).name()));
    this->setLowerPhaserAnim(this->loadPlistForAnimationWithName("shootPhaserAnim", typeid(this).name()));
    this->setLowerPhaserAnim(this->loadPlistForAnimationWithName("lowerPhaserAnim", typeid(this).name()));
    this->setLowerPhaserAnim(this->loadPlistForAnimationWithName("torsoHitAnim", typeid(this).name()));
    this->setLowerPhaserAnim(this->loadPlistForAnimationWithName("headHitAnim", typeid(this).name()));
    this->setLowerPhaserAnim(this->loadPlistForAnimationWithName("robotDeathAnim", typeid(this).name()));
    
   
}
EnemyRobot* EnemyRobot:: createWithSpriteFrameName(const char *pszSpriteFrameName){
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
    
    EnemyRobot *pobSprite = new EnemyRobot();
    pobSprite->init();
    if (pobSprite && pobSprite->initWithSpriteFrame(pFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }

    return NULL;

}
bool EnemyRobot:: init()
{
    bool bRet = GameCharacter::init();
    if( bRet )
    {
        isVikingWithinBoundingBox = false;
        isVikingWithinSight = false;
        gameObjectType = kEnemyTypeAlienRobot;
        this->initAnimations();
        srandom(time(NULL)); 
    }
    return bRet;
}
