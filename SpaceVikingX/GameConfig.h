//
//  GameConfig.h
//  SpaceVikingX
//
//  Created by An Jun on 13-6-15.
//
//

#ifndef SpaceVikingX_GameConfig_h
#define SpaceVikingX_GameConfig_h

//
// Supported Autorotations:
//		None,
//		UIViewController,
//		CCDirector
//
#define kGameAutorotationNone 0
#define kGameAutorotationCCDirector 1
#define kGameAutorotationUIViewController 2

//
// Define here the type of autorotation that you want for your game
//
// For iPhone 3GS and newer
//#define GAME_AUTOROTATION kGameAutorotationUIViewController

// For iPhone 3G and older (runs better)
#define GAME_AUTOROTATION kGameAutorotationCCDirector

#endif
