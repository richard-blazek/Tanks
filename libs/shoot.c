#include "shoot.h"
#include <stdlib.h>

void shoot_none(fighter *parent)
{
}

static fighter *add_shot(fighter *parent)
{
    fighter *shot = malloc(sizeof(fighter));
    shot->x = parent->x + parent->w / 4;
    shot->y = parent->y + parent->h / 4;
    shot->w = parent->w / 2;
    shot->h = parent->h / 2;
    shot->dx = parent->dx;
    shot->dy = parent->dy;
    shot->bloc = parent->bloc;
    shot->role = MISSILE;
    shot->level = 0;
    shot->xp = 0;
    shot->shot_health = shot->max_health = shot->health = parent->shot_health;
    shot->shot_speed = shot->speed = parent->shot_speed;
    shot->shooting_callback = shoot_none;
    shot->shooting_interval = shot->shooting_timeout = parent->shooting_interval;

    shot->next = parent->next;
    parent->next = shot;
    return shot;
}

void shoot_basic(fighter *parent)
{
    add_shot(parent);
}

void shoot_4(fighter *parent)
{
    fighter *shot1 = add_shot(parent);
    fighter *shot2 = add_shot(parent);
    shot2->dx = -shot1->dx;
    shot2->dy = -shot1->dy;
    fighter *shot3 = add_shot(parent);
    shot3->dx = -shot1->dy;
    shot3->dy = shot1->dx;
    fighter *shot4 = add_shot(parent);
    shot4->dx = -shot3->dx;
    shot4->dy = -shot3->dy;
}

void shoot_2(fighter *parent)
{
    fighter *shot1 = add_shot(parent);
    shot1->x -= parent->w / 4;
    fighter *shot2 = add_shot(parent);
    shot2->x += parent->w / 4;
}

void shoot_big(fighter *parent)
{
    fighter *shot = add_shot(parent);
    shot->x -= parent->w / 4;
    shot->y -= parent->h / 4;
    shot->w *= 2;
    shot->h *= 2;
}

void shoot_navigated(fighter *parent)
{
    fighter *shot = add_shot(parent);
    shot->role = SHOOTER;
}

void shoot_swarm(fighter *parent)
{
    fighter *shot = add_shot(parent);
    shot->role = SHOOTER;
    shot->shooting_callback = shoot_navigated;
    shot->shot_speed *= 1.25;
}
