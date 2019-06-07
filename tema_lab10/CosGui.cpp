#include "produs_dialog.h"
#include "CosGui.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
//\e#include <>

void CosGui::func_generate()
{
	qDebug() << "merje";
	int k = QInputDialog::getInt(this, "Magazin", "Please enter a number of random elements:", 5, 1);
	sc.genereaza_cos(k);
}

void CosGui::func_save()
{
	qDebug() << "merje";
	QString name = QFileDialog::getSaveFileName(this, "Magazin", "", "CSV Files(*.csv);;All Files(*.*)");
	if (name != "")
		sc.salveaza_cos(name.toStdString());
}

void CosGui::func_clear()
{
	sc.goleste_cos();
	QMessageBox::warning(this, "Magazin", "Cart successfully emptied");
}

CosGui::CosGui(service_cos& sc) : QWidget(), Observer(), sc{sc}
{
	this->setMinimumWidth(640);
	this->setMinimumHeight(350);

	qDebug() << "merje";

	sc.addObserver(this);
	InitializeLayout();
	ConnectSemnals();
}


void CosGui::InitializeLayout()
{
	QHBoxLayout* lay = new QHBoxLayout;
	lay->addWidget(lista);

	QStringList ls;
	ls << "Nume" << "Tip" << "Pret" << "Producator";

	lista->setColumnCount(4);
	lista->setShowGrid(true);
	lista->verticalHeader()->setVisible(false);
	lista->setEditTriggers(QAbstractItemView::NoEditTriggers);
	lista->setSelectionBehavior(QAbstractItemView::SelectRows);
	lista->setSelectionMode(QAbstractItemView::SingleSelection);

	lista->setHorizontalHeaderLabels(ls);

	QVBoxLayout* buttons = new QVBoxLayout;
	buttons->addWidget(generateButton);
	buttons->addWidget(addButton);
	buttons->addWidget(saveButton);
	buttons->addWidget(clearButton);
	buttons->addStretch();
	buttons->addWidget(lab);

	lay->addLayout(buttons);
	this->setLayout(lay);
}

void CosGui::ConnectSemnals()
{
	QObject::connect(generateButton, SIGNAL(clicked()), this, SLOT(func_generate()));;
	QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(func_save()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(func_add()));
	QObject::connect(clearButton, SIGNAL(clicked()), this, SLOT(func_clear()));
}

void CosGui::update()
{
	//lab->setText("PSD-u-i cel mai bun");
	lista->setRowCount(0);
	for (const auto* g : sc.get_cos())
	{
		qDebug() << QString::fromStdString(g->get_nume());
		lista->insertRow(lista->rowCount());
		lista->setItem(lista->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(g->get_nume())));
		lista->setItem(lista->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(g->get_tip())));
		lista->setItem(lista->rowCount() - 1, 2, new QTableWidgetItem(QString::number(g->get_pret())));
		lista->setItem(lista->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(g->get_producator())));
	}
}


CosGui::~CosGui()
{
	sc.removeObserver(this);
}