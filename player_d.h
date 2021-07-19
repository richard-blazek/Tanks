#pragma once

class Player: public Shooter
{
private:
	SDL::KeyboardState kb;
	uint32 xp=0, level=1;
	static void Shoot4(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower);
	static void DoubleShoot(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower);
	static void BigShoot(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower);
	static void QuickShoot(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower);
	static void Shoot5(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower);
	static void Shoot8(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower);
public:
	using Shooter::Shooter;
	virtual void Action(gui::Init& g, Fighters& fighters)override;
	uint32 GetXP()const;
	uint32 NextXP()const;
	uint32 GetLevel()const;
	void AddXP(gui::Init& g, uint32 xp);
	virtual void DrawOn(SDL::Renderer& rend)override;
};