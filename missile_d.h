#pragma once

class Missile: public Fighter
{
protected:
	Shooter& creator;
	uint32 attack;
	bool Out()const;
	virtual bool IsEnemy(Fighter* second)override;
public:
	Missile(Vector move, uint32 health, int squaresize, Shooter& creator);
	Shooter& GetCreator()const;
	virtual void Action(gui::Init& g, Fighters& fighters)override;
	virtual void Attack(gui::Init& g, Fighter* attacked)override;
	virtual void BeAttacked(gui::Init& g, uint32 damage, Fighter* attacker)override;
	virtual void DrawOn(SDL::Renderer& rend)override;
};