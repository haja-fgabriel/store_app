#include "Observable.h"



Observable::Observable()
{
}

void Observable::addObserver(Observer * obs)
{
	Observers.push_back(obs);
}

void Observable::removeObserver(Observer * obs)
{
	Observers.erase(std::remove(Observers.begin(), Observers.end(), obs), Observers.end());
}


void Observable::notify()
{
	for (auto* ob : Observers) ob->update();
}

Observable::~Observable()
{
}
