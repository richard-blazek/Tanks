#pragma once

bool Missile::Out()const
{
	return move.begin.x<0||move.begin.y<0||move.begin.x>screensize.x-square.x||move.begin.y>screensize.y-square.x;
}
bool Missile::IsEnemy(Fighter* second)
{
	return Fighter::IsEnemy(second)&&dynamic_cast<Shooter*>(second)!=&creator&&(dynamic_cast<Missile*>(second)?&dynamic_cast<Missile*>(second)->creator!=&creator:true);
}
Missile::Missile(Vector move, uint32 health, int squaresize, Shooter& creator)
	:Fighter(move, health, squaresize), attack(health), creator(creator){}
Shooter& Missile::GetCreator()const
{
	return creator;
}
void Missile::Action(gui::Init& g, Fighters& fighters)
{
	Move();
	Fighter::Action(g, fighters);
	if(Out())
	{
		health=0;
	}
}
void Missile::DrawOn(SDL::Renderer& rend)
{
	Fighter::DrawOn(rend, SDL::Color(0,0,200));
}
void Missile::Attack(gui::Init& g, Fighter* attacked)
{
	attacked->BeAttacked(g, attack, this);
}
void Missile::BeAttacked(gui::Init& g, uint32 damage, Fighter* attacker)
{
	health=(damage>0)?0:health;
}