//
//  EnemyRobot.h
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#ifndef __SpaceVikingX__EnemyRobot__
#define __SpaceVikingX__EnemyRobot__

#include "cocos2d.h"
#include "GameCharacter.h"
class EnemyRobot:public GameCharacter{
public:
    bool isVikingWithinBoundingBox;
    bool isVikingWithinSight;
    
    GameCharacter *vikingCharacter;
    virtual bool init();
    virtual ~EnemyRobot();
    void shootPhaser();
    void initAnimations();
    static EnemyRobot*  createWithSpriteFrameName(const char *pszSpriteFrameName);
    void changeState(CharacterStates newState);
    CCRect eyesightBoundingBox();
    void updateStateWithDeltaTime(float deltaTime, CCArray *listOfGameObjects);
    CCRect AdjustedBoundingBox();
    CC_SYNTHESIZE(GameplayLayerDelegate*, delegate, Delegate)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, robotWalkingAnim, RobotWalkingAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, raisePhaserAnim, RaisePhaserAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, shootPhaserAnim, ShootPhaserAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, lowerPhaserAnim, LowerPhaserAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, torsoHitAnim, TorsoHitAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, headHitAnim, HeadHitAnim)
    CC_SYNTHESIZE_RETAIN(CCAnimation*, robotDeathAnim, RobotDeathAnim)
    CREATE_FUNC(EnemyRobot);
};

#endif /* defined(__SpaceVikingX__EnemyRobot__) */
