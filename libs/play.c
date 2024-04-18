#include "play.h"
#include "shoot.h"
#include "io.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

static bool collide(fighter *f1, fighter *f2)
{
    return f1->x + f1->w >= f2->x && f1->y + f1->h >= f2->y
        && f2->x + f2->w >= f1->x && f2->y + f2->h >= f1->y;
}

static float distance(fighter *f1, fighter *f2)
{
    float dx = f1->x - f2->x, dy = f1->y - f2->y;
    return sqrtf(dx * dx + dy * dy);
}

static fighter *find_the_player(fighter *player)
{
    for (fighter *it = player; it; it = it->next)
    {
        if (it->role == PLAYER)
        {
            return it;
        }
    }
    return 0;
}

static fighter *find_closest_enemy(fighter *player, fighter *me)
{
    fighter *enemy = 0;
    for (fighter *it = player; it; it = it->next)
    {
        if (it->bloc != me->bloc && (!enemy || distance(it, me) < distance(enemy, me)))
        {
            enemy = it;
        }
    }
    return enemy;
}

static void move_fighter(fighter *me)
{
    float delta = me->dx * me->dx + me->dy * me->dy;
    float coef = me->speed / sqrt(delta < 1 ? 1 : delta);
    me->x += me->dx * coef;
    me->y += me->dy * coef;
}

static void hit_enemies(fighter *player, fighter *me)
{
    for (fighter *it = player; it; it = it->next)
    {
        if (it->bloc != me->bloc && it->health > 0 && collide(it, me))
        {
            it->health -= me->damage;
            if (it->health <= 0 && me->bloc == FRIEND)
            {
                player->xp += it->xp;
            }
        }
    }
}

static void fire_shots(fighter *me)
{
    if (me->shooting_timeout <= 0)
    {
        me->shooting_callback(me);
        me->shooting_timeout = me->shooting_interval;
    }
}

static void regenerate(fighter *me)
{
    if (me->shooting_timeout > 0)
    {
        me->shooting_timeout -= 1;
    }
    if (me->health < me->max_health)
    {
        ++me->health;
    }
}

static void change_direction_towards(fighter *me, float x, float y)
{
    me->dx = x - me->x;
    me->dy = y - me->y;
}

void play_missile(fighter *player, fighter *missile)
{
    move_fighter(missile);
    hit_enemies(player, missile);
}

void play_shooter(fighter *player, fighter *me)
{
    fighter *target = find_closest_enemy(player, me);
    if (target)
    {
        change_direction_towards(me, target->x, target->y);
    }
    move_fighter(me);
    hit_enemies(player, me);
    regenerate(me);
    fire_shots(me);
}

static void level_up(fighter *player)
{
    if (player->xp < 1.0)
    {
        return;
    }
    player->xp -= 1.0;
    player->level += 1;

    int selected = io_dialog("What do you want to improve?", "Speed|Health|Body damage|Missile damage");
    if (selected == 0 && player->speed < player->w / 2)
    {
        player->speed *= 1.25;
    }
    else if (selected == 1 && player->max_health < INT_MAX / 4)
    {
        player->max_health += player->max_health / 4;
        player->health += (player->health + player->max_health) / 2;
    }
    else if (selected == 2 && player->damage < INT_MAX / 4)
    {
        player->damage += player->damage / 4;
    }
    else if (selected == 3 && player->shot_damage < INT_MAX / 4)
    {
        player->shot_damage += player->shot_damage / 4;
    }

    if (player->level == 10)
    {
        int selected = io_dialog("Which tank improvement do you want?", "Four directions|Double shooting");
        if (selected == 0)
        {
            player->shooting_callback = shoot_4;
        }
        else
        {
            player->shooting_callback = shoot_2;
        }
    }
    else if (player->level == 20)
    {
        if (player->shooting_callback == shoot_2)
        {
            int selected = io_dialog("Which tank improvement do you want?", "Big missiles|Quick shooting");
            if (selected == 0)
            {
                player->shooting_callback = shoot_big;
                player->shot_damage *= 2;
            }
            else
            {
                player->shooting_interval /= 2;
                player->shooting_timeout = 0;
                player->shot_speed *= 2;
            }
        }
        else
        {
            int selected = io_dialog("Which tank improvement do you want?", "Navigated missiles|Swarm missiles");
            if (selected == 0)
            {
                player->shooting_interval = 1;
                player->shooting_callback = shoot_navigated;
            }
            else
            {
                player->shooting_interval *= 2;
                player->shooting_callback = shoot_swarm;
            }
        }
    }
}

void play_player(fighter *player)
{
    int dx, dy;
    io_arrows(&dx, &dy);
    player->dx = dx;
    player->dy = dy;
    move_fighter(player);
    regenerate(player);

    if (io_click())
    {
        int x, y;
        io_mouse_position(&x, &y);
        change_direction_towards(player, x, y);
        fire_shots(player);
    }
    hit_enemies(player, player);
    level_up(player);
}
