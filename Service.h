#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "hgevector.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <memory>

// forward class declarations
class Objects;
class Scene;

// extern declarations
extern HGE* hge ;
extern Objects* objects;
extern Scene* scene;
extern unsigned short lives;
extern float dt;

// enumerations
enum weapon_type { MACHINE_GUN, CANNON, ROCKET_LAUNCHER };
enum packet_type { BULLET, SHELL, ROCKET };
enum monster_type { BEAST, DAEMON, REPTILE };
enum game_errors { LOAD_SCENE_SOURCES, LOAD_TANK_SOURCES, LOAD_WEAPON_SOURCES, 
	LOAD_PACKET_SOURCES, LOAD_MONSTER_SOURCES, UNKNOWN_ERROR };

// constants
const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 768;
const float TILE_STEP = 32.0f;
const float ANGLE_VELOCITY = 1.0f;

#endif