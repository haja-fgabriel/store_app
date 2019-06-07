#pragma once

#include "Observer.h"
#include <vector>
#include <algorithm>

class Observable
{

public:
	Observable();

	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);
	void notify();

	~Observable();

private:
	std::vector<Observer*> Observers;
};

