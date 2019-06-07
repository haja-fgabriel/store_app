#pragma once

#include "produs.h"
#include <QDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QFormLayout>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QtWidgets/QLabel>

class produs_dialog : public QDialog
{

	Q_OBJECT

private:
	QString old_prd_name;

	QLineEdit* name_textbox = new QLineEdit;
	QLineEdit* type_textbox = new QLineEdit;
	QLineEdit* price_textbox = new QLineEdit;
	QLineEdit* manufacturer_textbox = new QLineEdit;


public slots:

public:
	static produs update_form(const QString& st);

	produs get_prod();

	produs_dialog(QWidget* parent, const QString& title, const QString& old_prod_name);
	void make_layout();
};

class produs_dialog_error : public std::exception { };