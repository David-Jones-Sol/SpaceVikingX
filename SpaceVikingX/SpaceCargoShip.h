//
//  SpaceCargoShip.h
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#ifndef __SpaceVikingX__SpaceCargoShip__
#define __SpaceVikingX__SpaceCargoShip__


#include "GameObject.h"
class SpaceCargoShip:public GameObject{
public:
    virtual bool init();
   
    bool hasDroppedMallet;
    void dropCargo();
    static  SpaceCargoShip*  createWithSpriteFrameName(const char *pszSpriteFrameName);
    CC_SYNTHESIZE(GameplayLayerDelegate*, delegate, Delegate)
};

#endif /* defined(__SpaceVikingX__SpaceCargoShip__) */
