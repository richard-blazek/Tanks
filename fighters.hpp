#pragma once

Fighters::Fighters(Fighter* player):list(1)
{
	list[0]=player;
}
void Fighters::Add(Fighter* fighter)
{
	list.push_back(fighter);
}
size_t Fighters::size()const
{
	return list.size();
}
Fighter* Fighters::operator[](size_t i)const
{
	return list[i];
}
Fighter*& Fighters::operator[](size_t i)
{
	return list[i];
}

Fighters::~Fighters()
{
    for(auto& x: list)
	{
		delete x;
		x=nullptr;
	}
}
void Fighters::DrawFighters(SDL::Renderer& rend)
{
	for(auto& x: list)
	{
		x->DrawOn(rend);
	}
}
AliveStruct Fighters::AliveFighters()const
{
	AliveStruct isAlive={0,0,0};
	for(auto& x: list)
	{
		if(typeid(*x)==typeid(Player)&&x->GetHealth()!=0)
		{
			isAlive.player=1;
		}
		else if(typeid(*x)==typeid(Fighter))
		{
			isAlive.system=1;
		}
		else if(typeid(*x)!=typeid(Missile))
		{
			isAlive.enemies=1;
		}
	}
	return isAlive;
}
void Fighters::DoActions(gui::Init& g)
{
	for(size_t i=0; i<list.size(); ++i)
	{
		list[i]->Action(g, *this);
	}
}
void Fighters::Clean()
{
	for(size_t i=0; i<list.size(); ++i)
	{
		if(list[i]->GetHealth()==0&&typeid(*list[i])!=typeid(Player))
		{
			delete list[i];
			list.erase(list.begin()+i);
		}
	}
}
vector<Fighter*>::iterator Fighters::begin()
{
	return list.begin();
}
vector<Fighter*>::iterator Fighters::end()
{
	return list.end();
}