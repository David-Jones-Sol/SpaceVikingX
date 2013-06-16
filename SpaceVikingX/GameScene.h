//
//  GameScene.h
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#ifndef __SpaceVikingX__GameScene__
#define __SpaceVikingX__GameScene__

#include "cocos2d.h"
#include "GameplayLayer.h"
#include "BackgroundLayer.h"


USING_NS_CC;
class GameScene:public CCScene{
public:
    virtual bool init();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__SpaceVikingX__GameScene__) */
