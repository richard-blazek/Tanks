#pragma once

using Point=geometry::Point<double>;
using Line=geometry::Line<Point, double>;
using Vector=geometry::Vector<Point, double, double>;

class Fighter
{
protected:
	Vector move;
	uint32 health, maxhealth;
	void Heal();
	void Move();
	void ControlLimits();
	void DrawOn(SDL::Renderer& rend, SDL::Color col);
public:
	virtual bool IsEnemy(Fighter* second);
	const SDL::Point square;
	static constexpr SDL::Point screensize=SDL::Point(1000, 640)*scale;
	virtual ~Fighter()=default;
	Fighter(Vector move, uint32 health, int squaresize);
	uint32 GetHealth()const;
	uint32 GetMaxHealth()const;
	uint32 GetSpeed()const;
	Point GetPosition()const;
	Point GetSquare()const;
	SDL::Angle GetRotation()const;
	virtual void BeAttacked(gui::Init& g, uint32 damage, Fighter* attacker);
	virtual void Attack(gui::Init& g, Fighter* attacked);
	virtual void Action(gui::Init& g, Fighters& fighters);
	virtual void DrawOn(SDL::Renderer& rend);
};