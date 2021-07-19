#pragma once

void Shooter::DefaultShoot(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower)
{
	fighters.Add(new Missile(Vector{obj.move.begin+obj.square/4, obj.move.move.lenght*5, Vector(Line(obj.move.begin+obj.square/4, target)).move.angle}, obj.shootpower, obj.square.x/2, obj));
}
void Shooter::Shoot(Fighters& fighters, Point target, uint32 shootpower)
{
	shoot(fighters, *this, target, shootpower);
}
Shooter::Shooter(Vector move, uint32 health, uint32 squaresize, uint32 shootpower, uint32 pause, Callback shoot)
	:Fighter(move, health, squaresize), shootpower(shootpower), interval(pause), shoot(shoot) {}
uint32 Shooter::GetShootPower()const
{
	return shootpower;
}
bool Shooter::IsEnemy(Fighter* second)
{
	if(auto mis=dynamic_cast<Missile*>(second))
	{
        return &mis->GetCreator()!=this;
	}
	return Fighter::IsEnemy(second);
}
void Shooter::Action(gui::Init& g, Fighters& fighters)
{
	Fighter::Action(g, fighters);
	Move();
	ControlLimits();
	interval.Continue();
}