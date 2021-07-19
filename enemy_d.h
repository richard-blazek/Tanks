#pragma once

class Enemy: public Shooter
{
protected:
	size_t i=0;
    Fighter* goal=nullptr;
public:
	using Shooter::Shooter;
	virtual void Action(gui::Init& g, Fighters& fighters)override;
	virtual void DrawOn(SDL::Renderer& rend)override;
};