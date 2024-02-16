#pragma once

#include "interval.h"

struct AliveStruct{uint8 player:1, enemies:1, system:1;};

class Player;
class Fighter;
class Shooter;
class Missile;
class Fighters;

#include "fighter_d.h"
#include "missile_d.h"
#include "shooter_d.h"
#include "enemy_d.h"
#include "player_d.h"
#include "fighters_d.h"