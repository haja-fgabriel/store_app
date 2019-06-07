#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QLabel>

#include "serviceCos.h"
#include "Observer.h"

class CosGui : public QWidget, private Observer
{
	Q_OBJECT

private:
	QTableWidget* lista = new QTableWidget;
	QPushButton* addButton = new QPushButton("&Add");
	QPushButton* generateButton = new QPushButton("&Generate");
	QPushButton* saveButton = new QPushButton("&Save");
	QPushButton* clearButton = new QPushButton("&Clear");
	QLabel* lab = new QLabel("MUiE PSD");

	service_cos& sc;

private slots:
	void func_generate();
	void func_save();
	void func_clear();

public:
	CosGui(service_cos& sc);
	void InitializeLayout();
	void ConnectSemnals();
	void update() override;
	~CosGui();
};

