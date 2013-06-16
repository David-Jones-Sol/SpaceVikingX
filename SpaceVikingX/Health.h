//
//  Health.h
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#ifndef __SpaceVikingX__Health__
#define __SpaceVikingX__Health__

#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;
class Health:public GameObject{
public:
    virtual  ~Health();
    virtual  bool init();
    void initAnimations();
    static Health*  createWithSpriteFrameName(const char *pszSpriteFrameName);
    void changeState(CharacterStates newState);
    void updateStateWithDeltaTime(float dt,CCArray *listOfGameObjects);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, healthAnim, HealthAnim)
};


#endif /* defined(__SpaceVikingX__Health__) */
