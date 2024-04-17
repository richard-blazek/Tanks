#pragma once

#include "interval.hpp"

struct AliveStruct{uint8 player:1, enemies:1, system:1;};

class Player;
class Fighter;
class Shooter;
class Missile;
class Fighters;

#include "fighter_d.hpp"
#include "missile_d.hpp"
#include "shooter_d.hpp"
#include "enemy_d.hpp"
#include "player_d.hpp"
#include "fighters_d.hpp"