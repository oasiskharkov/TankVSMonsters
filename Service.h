#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "hgevector.h"
#include "hgeFont.h"
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
extern unsigned short attempts;
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
const int MAX_MONSTER_COUNT = 10;
const float SURVIVAL_TIME = 300.0f;

const float TANK_ANGLE_VELOCITY = 1.0f;
const float TANK_SPEED = 100.0f;
const float TANK_ARMOR = 0.1f;
const float TANK_HEALTH = 1.0f;

const float BULLET_SPEED = 350.0f;
const float SHELL_SPEED = 250.0f;
const float ROCKET_SPEED = 150.0f;

const float BULLET_DAMAGE = 0.2f;
const float SHELL_DAMAGE = 0.5f;
const float ROCKET_DAMAGE = 0.8f;

const float BULLET_SHIFT = 25.0f;
const float SHELL_SHIFT = 35.0f;
const float ROCKET_SHIFT = 10.0f;

const float BEAST_HEALTH = 0.3f;
const float DAEMON_HEALTH = 0.6f;
const float REPTILE_HEALTH = 0.9f;

const float BEAST_ARMOR = 0.9f;
const float DAEMON_ARMOR = 0.6f;
const float REPTILE_ARMOR = 0.3f;

const float BEAST_DAMAGE = 0.2f;
const float DAEMON_DAMAGE = 0.5f;
const float REPTILE_DAMAGE = 0.8f;

const float BEAST_SPEED = 80.0f;
const float DAEMON_SPEED = 60.0f;
const float REPTILE_SPEED = 40.0f;

const float TANK_RADIUS = 31.0f;
const float MONSTER_RADIUS = 16.0f;
const float PACKET_RADIUS = 10.0f;

#endif