#include "fighters.h"
#include "play.h"
#include "shoot.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

void fighters_play(fighter *player)
{
    for (fighter *it = player; it; it = it->next)
    {
        if (it->role == SHOOTER) play_shooter(player, it);
        else if (it->role == MISSILE) play_missile(player, it);
        else if (it->role == PLAYER) play_player(player);
    }
}

int fighters_remaining(fighter *player)
{
    int alive = 0;
    for (fighter *it = player; it; it = it->next)
    {
        alive |= it->bloc;
    }
    return alive;
}

static bool out_of_bounds(fighter *me, int w, int h)
{
    return me->x < 0 || me->y < 0 || me->x + me->w > w || me->y + me->h > h;
}

static void move_inside_bounds(fighter *me, int w, int h)
{
    me->x = fmin(w - me->w, fmax(0, me->x));
    me->y = fmin(h - me->h, fmax(0, me->y));
}

static void check_bounds(fighter *me, int w, int h)
{
    if (out_of_bounds(me, w, h) && me->role == MISSILE)
    {
        me->health = 0;
    }
    move_inside_bounds(me, w, h);
}

fighter *fighters_clean(fighter *player, int w, int h)
{
    fighter **it = &player;
    while (*it)
    {
        check_bounds(*it, w, h);
        if ((*it)->health <= 0)
        {
            fighter *next = (*it)->next;
            free(*it);
            *it = next;
        }
        else
        {
            it = &(*it)->next;
        }
    }
    return player;
}

void fighters_free(fighter *player)
{
    if (player)
    {
        for (fighter *it = player->next; player; player = it, it = it->next)
        {
            free(player);
        }
    }
}

fighter *fighters_spawn_player(float x, float y, int w, int h, float speed, float shot_speed, int max_health,
                               int shot_health, int shooting_interval, shooting_callback shooting_callback)
{
    fighter *player = malloc(sizeof(fighter));
    player->x = x;
    player->y = y;
    player->dx = player->dy = 0.0f;
    player->w = w;
    player->h = h;
    player->speed = speed;
    player->shot_speed = shot_speed;
    player->xp = 0.0f;
    player->health = player->max_health = max_health;
    player->shot_health = shot_health;
    player->level = 1;
    player->shooting_timeout = player->shooting_interval = shooting_interval;
    player->shooting_callback = shooting_callback;
    player->bloc = FRIEND;
    player->role = PLAYER;
    player->next = 0;
    return player;
}

void fighters_spawn_stone(fighter *player, float x, float y, int w, int h, int max_health)
{
    fighter *s = malloc(sizeof(fighter));
    s->x = x;
    s->y = y;
    s->shot_speed = s->speed = s->dx = s->dy = 0.0f;
    s->xp = max_health;
    s->w = w;
    s->h = h;
    s->health = s->max_health = max_health;
    s->shot_health = 0;
    s->level = 1;
    s->shooting_timeout = s->shooting_interval = 1;
    s->shooting_callback = shoot_none;
    s->bloc = SYSTEM;
    s->role = MISSILE;
    s->next = player->next;
    player->next = s;
}

void fighters_spawn_enemy(fighter *player, float x, float y, int w, int h, float speed, float shot_speed,
                          int max_health, int shot_health, int shooting_interval, shooting_callback shooting_callback)
{
    fighter *e = malloc(sizeof(fighter));
    e->x = x;
    e->y = y;
    e->dx = e->dy = 0.0f;
    e->w = w;
    e->h = h;
    e->speed = speed;
    e->shot_speed = shot_speed;
    e->xp = max_health;
    e->health = e->max_health = max_health;
    e->shot_health = shot_health;
    e->level = 1;
    e->shooting_timeout = e->shooting_interval = shooting_interval;
    e->shooting_callback = shooting_callback;
    e->bloc = ENEMY;
    e->role = SHOOTER;
    e->next = player->next;
    player->next = e;
}
