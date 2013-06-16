//
//  GameCharacter.cpp
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#include "GameCharacter.h"
int GameCharacter::getWeaponDamage(){
    CCLOG("getWeaponDamage should be overriden");
    return 0;
}
void GameCharacter::checkAndClampSpritePosition(){
    CCPoint currentSpritePosition = this->getPosition();
    if (currentSpritePosition.x < 24.0f) {
        this->setPosition(ccp(24.0f, currentSpritePosition.y));
    } else if (currentSpritePosition.x > 456.0f) {
        this->setPosition(ccp(456.0f, currentSpritePosition.y));
    }
}
