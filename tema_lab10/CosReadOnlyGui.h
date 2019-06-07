#pragma once

#include <QWidget>
#include "Observer.h"

class CosReadOnlyGui : public QWidget, private Observer
{
public:
	CosReadOnlyGui();

	void paintEvent();
	void update() override;

	~CosReadOnlyGui();
};

