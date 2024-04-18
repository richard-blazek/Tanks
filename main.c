#include "libs/io.h"
#include "libs/objects.h"
#include "libs/fighters.h"
#include "libs/play.h"
#include "libs/shoot.h"

#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(0));
	const int w = 1200, h = 800;
	io_init(w, h);

	fighter *player = fighters_spawn_player(w/2, h/2, 40, 40, 2, 10, 400, 10, 20, 10, shoot_basic);

	fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 2, 10, 0.5, 100, 10, 15, 10, shoot_basic);
	fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 1, 5, 0.8, 100, 10, 15, 20, shoot_basic);
	fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 1, 5, 0.8, 100, 10, 15, 20, shoot_basic);
	fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 0.4, 2, 1.5, 100, 10, 50, 40, shoot_basic);
	fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, 0.5, rand() % 80 + 40, 10);
	fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, 0.5, rand() % 80 + 40, 10);
	fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, 0.5, rand() % 80 + 40, 10);
	fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, 0.5, rand() % 80 + 40, 10);

	while(io_loop())
	{
		io_draw_clear();
		fighters_play(player);
		player = fighters_clean(player, w, h);
		
		for (fighter *it = player; it; it = it->next)
		{
			io_draw_fighter(it->x, it->y, it->w, it->h,
							it->bloc == ENEMY ? 200 : 32, it->bloc == FRIEND ? 200 : 32, it->role == MISSILE ? 128 : 32,
							1.0 * it->health / it->max_health);
		}
		if (player->role == PLAYER)
		{
			io_draw_xp(player->level, player->xp);
		}
		io_draw_update();
		
		if (player->role != PLAYER)
		{
			io_message("Game over - You're dead!");
			break;
		}

		int alive = fighters_remaining(player);
		if ((alive & ENEMY) == 0)
		{
			io_message("Victory - You won");
			break;
		}
		else if (rand() % 100 == 0 || (alive & SYSTEM) == 0)
		{
			float size = rand() / (float)RAND_MAX + 0.2;
			fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, size / player->level, size * 100, 10);
		}
		else if (rand() % (clock() < 60000 ? 500 : 100) == 0)
		{
			float size = rand() / (float)RAND_MAX + 0.2;
			fighters_spawn_enemy(player, rand() % w, rand() % h, size * 40, size * 40, 1 / size, 8, size / player->level, 100 * size, 10, 50 * size, 50, shoot_basic);
		}
	}

	io_quit();
	return 0;
}
