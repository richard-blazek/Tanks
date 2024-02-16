#pragma once

class Fighters
{
private:
	vector<Fighter*> list;
public:
    Fighters(Fighter* player);
    ~Fighters();
    void Add(Fighter* fighter);
    size_t size()const;
    Fighter*& operator[](size_t i);
    Fighter* operator[](size_t i)const;
	void Clean();
	void DoActions(gui::Init& g);
	AliveStruct AliveFighters()const;
	void DrawFighters(SDL::Renderer& rend);
	vector<Fighter*>::iterator begin();
	vector<Fighter*>::iterator end();
};