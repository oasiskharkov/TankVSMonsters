#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include <vector>
#include <string>
#include <memory>

// forward class declarations
class Objects;
class Scene;

// extern declarations
extern HGE* hge ;
extern Objects* objects;
extern Scene* scene;

// enumerations
enum weapon_type { MACHINE_GUN, CANNON, ROCKET_LAUNCHER };
enum game_errors { LOAD_SCENE_SOURCES };

// constants
const int GAME_WIDTH = 1024;
const int GAME_HEIGHT = 768;
const float TILE_STEP = 32.0f;

#endif