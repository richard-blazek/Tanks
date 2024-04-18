#include "libs/io.h"
#include "libs/objects.h"
#include "libs/fighters.h"
#include "libs/play.h"
#include "libs/shoot.h"

#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

int main()
{
	srand(time(0));
	const int w = 1000, h = 640;
	io_init(w, h);

	fighter *player = fighters_spawn_player(500, 300, 40, 40, 4, 5, 400, 20, 24, shoot_basic);

	fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 2, 10, 100, 15, 10, shoot_basic);
	fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 1, 5, 100, 15, 20, shoot_basic);
	fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 1, 5, 100, 15, 20, shoot_basic);
	fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 0.4, 2, 100, 50, 40, shoot_basic);
	fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);
	fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);
	fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);
	fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);

	while(!SDL_QuitRequested())
	{
		io_draw_clear();
		fighters_play(player);
		player = fighters_clean(player, w, h);
		
		for (fighter *it = player; it; it = it->next)
		{
			io_draw_fighter(it->x, it->y, it->w, it->h, it->bloc == ENEMY ? 200 : 32, it->bloc == FRIEND ? 200 : 32, 32, 1.0 * it->health / it->max_health);
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
		else if ((alive & SYSTEM) == 0)
		{
			fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);
			fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);
			fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);
			fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);
		}
		if (rand() % (clock() < 60000 ? 500 : 200) == 0)
		{
			int size = rand() % 3 + player->level;
			fighters_spawn_enemy(player, rand() % w, rand() % h, 40, 40, 3.0 / size, 2, 100 * size, 50 * size, 50, shoot_basic);
		}
		else if (rand() % 200 == 0)
		{
			fighters_spawn_stone(player, rand() % w, rand() % h, 20, 20, rand() % 80 + 40);
		}
		SDL_Delay(50);
	}

	io_quit();
	return 0;
}
