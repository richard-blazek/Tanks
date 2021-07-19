#pragma once

void Fighter::Heal()
{
	if(health<maxhealth&&health!=0)
	{
		++health;
	}
}
void Fighter::Move()
{
	move.begin=Line(move).end;
}
void Fighter::ControlLimits()
{
	if(move.begin.x<0)move.begin.x=0;
	if(move.begin.y<0)move.begin.y=0;
	if(move.begin.x>screensize.x-square.x)move.begin.x=screensize.x-square.x;
	if(move.begin.y>screensize.y-square.x)move.begin.y=screensize.y-square.x;
}
void Fighter::DrawOn(SDL::Renderer& rend, SDL::Color col)
{
	rend.Draw(SDL::Rect(GetPosition()/scale, square.x/scale), col);
	if(health!=maxhealth)
	{
		rend.Draw(SDL::Rect(GetPosition()/scale, square.x/scale*health/maxhealth, 2), SDL::Color(10,190,0));
		rend.Draw(SDL::Rect(GetPosition()/scale+Point(square.x/scale*health/maxhealth, 0), square.x/scale-square.x/scale*health/maxhealth, 2), SDL::Color(190,10,0));
	}
}
bool Fighter::IsEnemy(Fighter* second)
{
	return second!=this;
}
Fighter::Fighter(Vector move, uint32 health, int squaresize)
	:move(move), health(health), maxhealth(health), square({squaresize, squaresize}) {}
uint32 Fighter::GetHealth()const
{
	return health;
}
uint32 Fighter::GetMaxHealth()const
{
	return maxhealth;
}
uint32 Fighter::GetSpeed()const
{
	return move.move.lenght;
}
Point Fighter::GetPosition()const
{
	return move.begin;
}
Point Fighter::GetSquare()const
{
	return square;
}
SDL::Angle Fighter::GetRotation()const
{
	return move.move.angle;
}
void Fighter::BeAttacked(gui::Init& g, uint32 damage, Fighter* attacker)
{
	health=(health<damage)?0:health-damage;
	if(health==0)
	{
		if(auto player=dynamic_cast<Player*>(attacker))
		{
			player->AddXP(g, maxhealth);
		}
		else if(auto mis=dynamic_cast<Missile*>(attacker))
		{
            if(auto player=dynamic_cast<Player*>(&mis->GetCreator()))
			{
				player->AddXP(g, maxhealth);
			}
		}
	}
}
void Fighter::Attack(gui::Init& g, Fighter* attacked)
{
	attacked->BeAttacked(g, 10, this);
}
void Fighter::Action(gui::Init& g, Fighters& fighters)
{
	Heal();
	for(auto& fighter:fighters)
	{
		if(IsEnemy(fighter)&&SDL::Rect(fighter->GetPosition(), fighter->GetSquare()).Intersects(SDL::Rect(move.begin, square)))
		{
			Attack(g, fighter);
		}
	}
}
void Fighter::DrawOn(SDL::Renderer& rend)
{
	DrawOn(rend, SDL::Color(250,245,0));
}