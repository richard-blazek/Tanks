#pragma once

class Interval
{
private:
	uint32 waittime, timeleft=0;
public:
	Interval(uint32 time):waittime(time){}
	bool IsElapsed()const
	{
		return timeleft==0;
	}
	void Continue()
	{
		if(!IsElapsed())
		{
			--timeleft;
		}
	}
	void Refresh()
	{
		timeleft=waittime;
	}
	void Reset(uint32 time)
	{
        waittime=time;
        timeleft=0;
	}
	uint32 GetPause()const
	{
		return waittime;
	}
};