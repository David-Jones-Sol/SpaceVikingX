//
//  GameplayLayer.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "GameplayLayer.h"
#include "SpaceCargoShip.h"
#include "EnemyRobot.h"
#include "PhaserBullet.h"
#include "Mallet.h"
#include "Health.h"
GameplayLayer::~GameplayLayer(){
    CC_SAFE_DELETE(leftJoystick);
    CC_SAFE_DELETE(jumpButton);
    CC_SAFE_DELETE(attackButton);
}
bool GameplayLayer::init(){
    bool bRet = false;
    bRet = CCLayer::init();
	if ( bRet )
	{
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        this->setTouchEnabled(true);
        srandom(time(NULL)); // Seeds the random number generator
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->
        addSpriteFramesWithFile("scene1atlasiPhone.plist");
        sceneSpriteBatchNode =
        
        CCSpriteBatchNode::create("scene1atlasiPhone.png");
        
        this->addChild(sceneSpriteBatchNode,0);                // 3
        this->initJoystickAndButtons();                           // 4
        Viking *viking = Viking::createWithSpriteFrameName("sv_anim_1.png");
        viking->setJoystick(leftJoystick);
        viking->setjumpButton(jumpButton);
        viking->setattackButton(attackButton);
        viking->setPosition(ccp(screenSize.width*0.35f,screenSize.height*0.14f));
        viking->setCharacterHealth(100);
        
        sceneSpriteBatchNode->addChild(viking,kVikingSpriteZValue,kVikingSpriteTagValue);
        this->createObjectOfType(kEnemyTypeRadarDish, 100, ccp(screenSize.width*0.878f,screenSize.height*0.13f), 10);
        this->scheduleUpdate();
        this->schedule(schedule_selector(GameplayLayer::addEnemy), 10.f);
        this->createObjectOfType(kEnemyTypeSpaceCargoShip, 0, ccp(screenSize.width * -0.5f,screenSize.height * 0.74f), 50);
     
    }
    return true;
}
void GameplayLayer::addEnemy() {
    CCSize screenSize =CCDirector::sharedDirector()->getWinSize();

    RadarDish *radarDish = (RadarDish*)sceneSpriteBatchNode->getChildByTag(kRadarDishTagValue);

    if (radarDish != NULL) {
        
        if (radarDish->getCharacterState() != kStateDead) {
            this->createObjectOfType(kEnemyTypeAlienRobot, 100, ccp(screenSize.width * 0.195f,screenSize.height * 0.1432f), 2);
                 } else {
            this->unschedule(schedule_selector(GameplayLayer::addEnemy));
            
        }
    }
}
void GameplayLayer::createObjectOfType(GameObjectType objectType,int initialHealth,cocos2d::CCPoint spawnLocation,int ZValue ){
    if (objectType == kEnemyTypeRadarDish) {
        CCLOG("Creating the Radar Enemy");
        RadarDish *radarDish =RadarDish::createWithSpriteFrameName("radar_1.png");
        radarDish->setCharacterHealth(initialHealth);
        radarDish->setPosition(spawnLocation);
        sceneSpriteBatchNode->addChild(radarDish,ZValue,kRadarDishTagValue);
        
    }else if (kEnemyTypeAlienRobot == objectType) {
        CCLOG("Creating the Alien Robot");
        EnemyRobot *enemyRobot =EnemyRobot::createWithSpriteFrameName("an1_anim1.png");
        enemyRobot->setCharacterHealth(initialHealth);
        enemyRobot->setPosition(spawnLocation);
        enemyRobot->changeState(kStateSpawning);
        sceneSpriteBatchNode->addChild(enemyRobot,ZValue);
        enemyRobot->setDelegate(this);
      
      
    } else if (kEnemyTypeSpaceCargoShip == objectType) {
        CCLOG("Creating the Cargo Ship Enemy");
        
        SpaceCargoShip *spaceCargoShip =SpaceCargoShip::createWithSpriteFrameName("ship_2.png");
        spaceCargoShip->setDelegate(this);
        spaceCargoShip->setPosition(spawnLocation);
        sceneSpriteBatchNode->addChild(spaceCargoShip,ZValue);
       
       
    } else if (kPowerUpTypeMallet == objectType) {
        CCLOG("GameplayLayer -> Creating mallet powerup");
        Mallet *mallet =Mallet::createWithSpriteFrameName("mallet_1.png");
        mallet->setPosition(spawnLocation);
        sceneSpriteBatchNode->addChild(mallet);
       
    } else if (kPowerUpTypeHealth == objectType) {
        CCLOG("GameplayLayer-> Creating Health Powerup");
        Health *health =Health::createWithSpriteFrameName("sandwich_1.png");
        health->setPosition(spawnLocation);
        sceneSpriteBatchNode->addChild(health);

    }

}
void GameplayLayer::createPhaseWithDirection(PhaserDirection phaserDirection,cocos2d::CCPoint spawnPosition){
    CCLOG("Placeholder for chapter 5, see below");
    return;
}

void GameplayLayer::update(float deltaTime)
{
    CCArray *listOfGameObjects = sceneSpriteBatchNode->getChildren();
    GameCharacter* tempChar ;
    for (int i=0; i<listOfGameObjects->count(); ++i) {
        tempChar = (GameCharacter*)listOfGameObjects->objectAtIndex(i);
        tempChar->updateStateWithDeltaTime(deltaTime, listOfGameObjects);
    }

}
void GameplayLayer::initJoystickAndButtons() {
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCRect joystickBaseDimensions = CCRect(0, 0, 128.0f, 128.0f);
    CCRect jumpButtonDimensions = CCRect(0, 0, 64.0f, 64.0f);
    CCRect attackButtonDimensions =  CCRect(0, 0, 64.0f, 64.0f);
    CCPoint joystickBasePosition;
    CCPoint jumpButtonPosition;
    CCPoint attackButtonPosition;
    
    
    // The device is an iPhone or iPod touch.
    CCLOG("Positioning Joystick and Buttons for iPhone");
    joystickBasePosition = ccp(screenSize.width*0.07f,
                               screenSize.height*0.11f);
    
    jumpButtonPosition = ccp(screenSize.width*0.93f,
                             screenSize.height*0.11f);
    
    attackButtonPosition = ccp(screenSize.width*0.93f,
                               screenSize.height*0.35f);
    
    
    SneakyJoystickSkinnedBase *joystickBase =
    SneakyJoystickSkinnedBase::create();
    joystickBase->setPosition(joystickBasePosition);
    joystickBase->setBackgroundSprite(CCSprite::create("dpadDown.png"));
    
    joystickBase->setThumbSprite(CCSprite::create("joystickDown.png"));
    
    SneakyJoystick*  joystick=new SneakyJoystick();
    joystick->initWithRect(joystickBaseDimensions);
    joystick->autorelease();
    joystickBase->setJoystick(joystick);
    joystick->retain();
    leftJoystick = joystick;
    this->addChild(joystickBase);
    
    SneakyButtonSkinnedBase *jumpButtonBase = SneakyButtonSkinnedBase::create();
    
    jumpButtonBase->setPosition(jumpButtonPosition);
    jumpButtonBase->setDefaultSprite(CCSprite::create("jumpUp.png"));
    jumpButtonBase->setActivatedSprite(CCSprite::create("jumpDown.png"));
    jumpButtonBase->setPressSprite(CCSprite::create("jumpDown.png"));
    SneakyButton *button = new SneakyButton();
    button->initWithRect(jumpButtonDimensions);
    button->autorelease();
    jumpButtonBase->setButton(button);
    button->retain();
    jumpButton = button;
    
    jumpButton->setIsToggleable(false);
    this->addChild(jumpButtonBase);
    
    
    SneakyButtonSkinnedBase *attackButtonBase = SneakyButtonSkinnedBase::create();
    attackButtonBase->setPosition(attackButtonPosition);
    attackButtonBase->setDefaultSprite(CCSprite::create("handUp.png"));
    attackButtonBase->setActivatedSprite(CCSprite::create("handDown.png"));
    attackButtonBase->setPressSprite(CCSprite::create("handDown.png"));
    
    SneakyButton *aButton = new SneakyButton();
    aButton->autorelease();
    aButton->initWithRect(attackButtonDimensions);
    attackButtonBase->setButton(aButton);
    aButton->retain();
    attackButton = aButton;
    attackButton->setIsToggleable(false);
    this->addChild(attackButtonBase);
}
