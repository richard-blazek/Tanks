#pragma once

void Enemy::Action(gui::Init& g, Fighters& fighters)
{
	Shooter::Action(g, fighters);
	if(fighters[i]!=goal)
	{
		do
		{
			i=rand()%fighters.size();
		}while(!IsEnemy(fighters[i])||dynamic_cast<Missile*>(fighters[i]));
		goal=fighters[i];
	}
	move.move.angle=Vector(Line(move.begin, goal->GetPosition())).move.angle;
	if(interval.IsElapsed())
	{
		Shoot(fighters, goal->GetPosition(), shootpower);
		interval.Refresh();
	}
}
void Enemy::DrawOn(SDL::Renderer& rend)
{
	Fighter::DrawOn(rend, SDL::Color(255,0,0));
}