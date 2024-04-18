#ifndef __OBJECTS_H__
#define __OBJECTS_H__

typedef enum bloc bloc;
typedef enum role role;
typedef struct fighter fighter;
typedef void (*shooting_callback)(fighter *shooter);

enum bloc
{
    SYSTEM = (1 << 0),
    FRIEND = (1 << 1),
    ENEMY  = (1 << 2)
};

enum role
{
    SHOOTER,
    MISSILE,
    PLAYER
};

struct fighter
{
    float x, y, dx, dy, speed, shot_speed, xp;
    int w, h;
    int health, max_health, damage, shot_damage, level;
    int shooting_interval, shooting_timeout;
    shooting_callback shooting_callback;
    bloc bloc;
    role role;
    fighter *next;
};

#endif
