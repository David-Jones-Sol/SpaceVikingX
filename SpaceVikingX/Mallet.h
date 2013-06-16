//
//  Mallet.h
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#ifndef __SpaceVikingX__Mallet__
#define __SpaceVikingX__Mallet__

#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;
class Mallet:public GameObject{
public:
    virtual   ~Mallet();
    virtual bool init();
    static Mallet*  createWithSpriteFrameName(const char *pszSpriteFrameName);
    void initAnimations();
    void changeState(CharacterStates newState);
    void updateStateWithDeltaTime(float dt,CCArray *listOfGameObjects);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, malletAnim, MalletAnim)
    
};


#endif /* defined(__SpaceVikingX__Mallet__) */
