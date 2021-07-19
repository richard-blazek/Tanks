#pragma once

class Shooter: public Fighter
{
protected:
    using Callback=void(*)(Fighters&,Shooter&,Point,uint32);
    uint32 shootpower;
    Interval interval;
    Callback shoot;
    static void DefaultShoot(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower);
    void Shoot(Fighters& fighters, Point target, uint32 shootpower);
	virtual bool IsEnemy(Fighter* second)override;
public:
	Shooter(Vector move, uint32 health, uint32 squaresize, uint32 shootpower, uint32 pause, Callback shoot=DefaultShoot);
	uint32 GetShootPower()const;
	virtual void Action(gui::Init& g, Fighters& fighters)override;
};