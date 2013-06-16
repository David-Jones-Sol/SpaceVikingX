//
//  PhaserBullet.h
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#ifndef __SpaceVikingX__PhaserBullet__
#define __SpaceVikingX__PhaserBullet__

#include "cocos2d.h"
#include "GameCharacter.h"
USING_NS_CC;

class PhaserBullet:public GameCharacter{
private:
  
    PhaserDirection myDirection;
public:
    virtual ~PhaserBullet();
    virtual bool init();
    bool isOutsideOfScreen();
    void initAnimations();
    void  updateStateWithDeltaTime(float deltaTime,CCArray* listOfGameObjects);
    void changeState(CharacterStates newState);
    CC_SYNTHESIZE_RETAIN(CCAnimation*,firingAnim,FiringAnim);
    CC_SYNTHESIZE_RETAIN(CCAnimation*,travelingAnim,TravelingAnim);
    CREATE_FUNC(PhaserBullet);
};

#endif /* defined(__SpaceVikingX__PhaserBullet__) */
