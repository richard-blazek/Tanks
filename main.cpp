#include <typeinfo>
#include <memory>
#include <cstdlib>
#include "myframework/gui.h"

using namespace std;

constexpr int scale=15;

#include "decl.h"

#include "fighter.h"
#include "missile.h"
#include "shooter.h"
#include "enemy.h"
#include "player.h"
#include "fighters.h"

int main()
{
	srand(time(0));
	Player& player=*new Player(Vector(Point(500, 300)*scale, 1*scale, 0), 200, 20*scale, 10, 10);
	Fighters fighters(&player);
	fighters.Add(new Enemy(Vector(Point(rand()%980, rand()%620)*scale, 2*scale, 0), 100, 10*scale, 15, 10));
	fighters.Add(new Enemy(Vector(Point(rand()%980, rand()%620)*scale, 1*scale, 0), 200, 20*scale, 15, 20));
	fighters.Add(new Enemy(Vector(Point(rand()%980, rand()%620)*scale, 1*scale, 0), 200, 20*scale, 15, 20));
	fighters.Add(new Enemy(Vector(Point(rand()%980, rand()%620)*scale, scale/3, 0), 400, 40*scale, 50, 40));
	fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2*scale, 0), rand()%80+40, 20*scale));
	fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2*scale, 0), rand()%80+40, 20*scale));
	fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2*scale, 0), rand()%80+40, 20*scale));
	fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2*scale, 0), rand()%80+40, 20*scale));
	gui::Init g("font.ttf", 12);
	g.bg_color=SDL::Color(0,0,0);
	g.text_color=SDL::Color(255,255,255);
	g.button_color=SDL::Color(255,100,100);
	g.button_hover_color=SDL::Color(255,0,0);
	g.button_clicked_color=SDL::Color(200,0,0);
	SDL::Window screen("Tanks", SDL::Rect(20,30, Fighter::screensize/scale+Point(0, 10)));
	SDL::Renderer rend(screen);
	while(!SDL::events::Quit())
	{
		rend.Repaint(SDL::Color(245,250,255));
		fighters.DoActions(g);
		fighters.Clean();
		rend.SetViewport(SDL::Rect(0, 10, Fighter::screensize/scale));
		fighters.DrawFighters(rend);
		rend.SetViewportToDefault();
		rend.Draw(SDL::Rect(0, 0, Fighter::screensize.x/scale, 10), SDL::Color(190,190,190));
		rend.Draw(SDL::Rect(0, 0, Fighter::screensize.x*player.GetXP()/player.NextXP()/scale, 10), SDL::Color(100,255,0));
		g.Draw(rend, "Level: "+to_string(player.GetLevel()), SDL::Color(0,0,0), SDL::Rect(0,10,100,20));
		rend.Show();
		AliveStruct isAlive=fighters.AliveFighters();
		if(isAlive.player==0)
		{
			SDL::MessageBox::Show("Defeat", "You're dead!");
			break;
		}
		else if(isAlive.enemies==0)
		{
			SDL::MessageBox::Show("Victory", "Your enemies are dead!");
			break;
		}
		else if(isAlive.system==0)
		{
			fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2, 0), rand()%80+40, 20*scale));
			fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2, 0), rand()%80+40, 20*scale));
			fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2, 0), rand()%80+40, 20*scale));
			fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2, 0), rand()%80+40, 20*scale));
		}
		if(rand()%(clock()<60000?200:100)==0)
		{
			int size=rand()%3+player.GetLevel();
			fighters.Add(new Enemy(Vector(Point(rand()%980, rand()%620)*scale, scale*3/size, 0), 70*size, 10*(size-player.GetLevel()+1)*scale, 3*size, 6*size));
		}
		else if(rand()%200==0)
		{
			fighters.Add(new Fighter(Vector(Point(rand()%980, rand()%620)*scale, 2, 0), rand()%80+40, 20*scale));
		}
		SDL::Wait(50);
	}
	return 0;
}
