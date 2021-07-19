#pragma once

void Player::Shoot4(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower)
{
	fighters.Add(new Missile(Vector(obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle), obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector(obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(90)), obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector(obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(180)), obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector(obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(270)), obj.GetShootPower(), obj.GetSquare().x/2, obj));
}
void Player::DoubleShoot(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower)
{
	fighters.Add(new Missile(Vector(obj.GetPosition(), obj.GetSpeed()*5, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle), obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector(obj.GetPosition()+obj.GetSquare()/2, obj.GetSpeed()*5, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle), obj.GetShootPower(), obj.GetSquare().x/2, obj));
}
void Player::BigShoot(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower)
{
	fighters.Add(new Missile(Vector{obj.GetPosition(), obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition(), target)).move.angle}, obj.GetShootPower()*2, obj.GetSquare().x, obj));
}
void Player::QuickShoot(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower)
{
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*10.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
}
void Player::Shoot5(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower)
{
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(45)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(90)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle-SDL::Angle::FromDeg(45)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle-SDL::Angle::FromDeg(90)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
}
void Player::Shoot8(Fighters& fighters, Shooter& obj, Point target, uint32 shootpower)
{
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(45)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(90)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(135)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(180)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(225)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(270)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
	fighters.Add(new Missile(Vector{obj.GetPosition()+obj.GetSquare()/4, obj.GetSpeed()*5.0, Vector(Line(obj.GetPosition()+obj.GetSquare()/4, target)).move.angle+SDL::Angle::FromDeg(315)}, obj.GetShootPower(), obj.GetSquare().x/2, obj));
}
void Player::Action(gui::Init& g, Fighters& fighters)
{
	Fighter::Action(g, fighters);
	interval.Continue();
	if(kb.IsPressed(SDL::Scancode::Up))
	{
		move.move.angle=SDL::Angle::FromDeg(271);
		Move();
	}
	if(kb.IsPressed(SDL::Scancode::Down))
	{
		move.move.angle=SDL::Angle::FromDeg(90);
		Move();
	}
	if(kb.IsPressed(SDL::Scancode::Right))
	{
		move.move.angle=SDL::Angle::FromDeg(0);
		Move();
	}
	if(kb.IsPressed(SDL::Scancode::Left))
	{
		move.move.angle=SDL::Angle::FromDeg(180);
		Move();
	}
	ControlLimits();
	if((SDL::Cursor::PressedButtons()&SDL::MouseButtonMask::Left)!=SDL::MouseButtonMask::None&&interval.IsElapsed())
	{
		Shoot(fighters, SDL::Cursor::Position()*scale, shootpower);
		interval.Refresh();
	}
}
uint32 Player::GetXP()const
{
	return xp;
}
uint32 Player::NextXP()const
{
	return (level+1)*50;
}
uint32 Player::GetLevel()const
{
	return level;
}
void Player::AddXP(gui::Init& g, uint32 new_xp)
{
	xp+=new_xp;
	if(xp>=NextXP())
	{
		size_t selected=gui::DialogSelect(g, "Co chceš vylepšit?", {"Rychost +25%", "Zdraví +25%", "Síla střely +25%", "Rychlost střelby +25%"}, 250);
		if(selected==0)
		{
			move.move.lenght+=move.move.lenght/4;
		}
		else if(selected==1)
		{
			maxhealth+=maxhealth/4;
			health+=maxhealth/4;
		}
		else if(selected==2)
		{
			shootpower+=shootpower/4;
		}
		else if(selected==3)
		{
			interval.Reset(interval.GetPause()/1.25);
		}
		xp-=NextXP();
		++level;
		if(level==10)
		{
			size_t selected=gui::DialogSelect(g, "Čím chcete být?", {"Čtyřsměrný tank", "Dvojstřelný tank"});
			if(selected==0)
			{
				shoot=Shoot4;
			}
			else
			{
				shoot=DoubleShoot;
			}
		}
		if(level==25)
		{
			if(shoot==DoubleShoot)
			{
				size_t selected=gui::DialogSelect(g, "Čím chcete být?", {"Velkostřelný tank", "Rychlostřelný tank"});
				if(selected==0)
				{
					shoot=BigShoot;
				}
				else
				{
					interval.Reset(interval.GetPause()/2);
					shoot=QuickShoot;
				}
			}
			else
			{
				size_t selected=gui::DialogSelect(g, "Čím chcete být?", {"Osmisměrný tank", "Pětisměrný tank"});
				if(selected==0)
				{
					shoot=Shoot8;
				}
				else
				{
					shootpower=shootpower*8/5;
					shoot=Shoot5;
				}
			}
		}
	}
}
void Player::DrawOn(SDL::Renderer& rend)
{
	Fighter::DrawOn(rend, SDL::Color(0,255,0));
}