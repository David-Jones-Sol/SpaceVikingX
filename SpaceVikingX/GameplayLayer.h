//
//  GameplayLayer.h
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#ifndef __SpaceVikingX__GameplayLayer__
#define __SpaceVikingX__GameplayLayer__

#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystickSkinnedBase.h"
#include "Constants.h"
#include "CommonProtocols.h"
#include "Viking.h"
#include "RadarDish.h"
USING_NS_CC;
class GameplayLayer:public CCLayer,public GameplayLayerDelegate{
public:
    virtual bool init();
    virtual ~GameplayLayer();
    void initJoystickAndButtons();
    void createObjectOfType(GameObjectType objectType,int initialHealth,CCPoint spawnLocation,int ZValue );
    void createPhaseWithDirection(PhaserDirection phaserDirection,CCPoint spawnPosition);
    void update(float deltaTime);
    void addEnemy();
    CREATE_FUNC(GameplayLayer);

private:
    CCSprite *vikingSprite;
    SneakyJoystick *leftJoystick;
    SneakyButton *jumpButton;
    SneakyButton *attackButton;
    CCSpriteBatchNode *sceneSpriteBatchNode;
};

#endif /* defined(__SpaceVikingX__GameplayLayer__) */
