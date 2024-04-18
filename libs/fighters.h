#ifndef __FIGHTERS_H__
#define __FIGHTERS_H__

#include "objects.h"

void fighters_play(fighter *player);
int fighters_remaining(fighter *player);
fighter *fighters_clean(fighter *player, int w, int h);
void fighters_free(fighter *player);

fighter *fighters_spawn_player(float x, float y, int w, int h, float speed, float shot_speed, int max_health,
    int shot_health, int shooting_interval, shooting_callback shooting_callback);

void fighters_spawn_stone(fighter *player, float x, float y, int w, int h, int max_health);

void fighters_spawn_enemy(fighter *player, float x, float y, int w, int h, float speed, float shot_speed, int max_health,
    int shot_health, int shooting_interval, shooting_callback shooting_callback);

#endif
