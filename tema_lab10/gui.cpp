#include <QDebug>
#include <QColor>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QHeaderView>
#include <QCloseEvent>

#include "gui.h"
#include "produs_dialog.h"
#include "CosGui.h"

tema_lab10::tema_lab10(service& serv, service_cos& srv_cos, QWidget *parent)
	: QMainWindow(parent), serv_cos{ srv_cos }, srv{serv}
{
	ui.setupUi(this);

	delete ui.mainToolBar;
	this->setMinimumWidth(960);

	prepare_elements();
	initialize_elements();
	refresh_list();
}

QWidget* tema_lab10::make_form()
{
	QWidget* newForm = new QWidget;
	newForm->setMaximumHeight(120);
	newForm->setMinimumHeight(120);

	QLabel* name_label = new QLabel("Name");
	QLabel* type_label = new QLabel("Type");
	QLabel* price_label = new QLabel("Price");
	QLabel* manufacturer_label = new QLabel("Manufacturer");

	QFormLayout* form_layout = new QFormLayout;
	form_layout->setContentsMargins(0, 0, 0, 0);

	//type_textbox->setValidator(QDoubleValidator());
	
	form_layout->addRow(name_label, name_textbox);
	form_layout->addRow(type_label, type_textbox);
	form_layout->addRow(price_label, price_textbox);
	form_layout->addRow(manufacturer_label, manufacturer_textbox);

	newForm->setLayout(form_layout);
	return newForm;
}

QWidget* tema_lab10::make_add_upd_button_row()
{
	QWidget* add_upd_button_row = new QWidget;
	add_upd_button_row->setMaximumHeight(30);
	add_upd_button_row->setMinimumHeight(30);

	QHBoxLayout* add_upd_button_row_layout = new QHBoxLayout;
	add_upd_button_row_layout->setContentsMargins(0, 0, 0, 0);

	add_upd_button_row_layout->addWidget(add_button);
	add_upd_button_row_layout->addWidget(update_button);

	add_upd_button_row->setLayout(add_upd_button_row_layout);
	return add_upd_button_row;
}

QWidget* tema_lab10::make_cart_button_row()
{
	QWidget* newWnd = new QWidget;
	QHBoxLayout* cart_button_row_layout = new QHBoxLayout;
	cart_button_row_layout->addWidget(cart_button);
	cart_button_row_layout->addWidget(cart_read_only_button);
	newWnd->setLayout(cart_button_row_layout);
	//newWnd->setContentsMargins(0, 0, 0, 0);
	cart_button_row_layout->setContentsMargins(0, 0, 0, 0);
	return newWnd;
}

QWidget* tema_lab10::make_right_pane_buttons_widget()
{
	QWidget* newWnd = new QWidget;
	newWnd->setMaximumHeight(85);
	newWnd->setMinimumHeight(85);
	QVBoxLayout* lay = new QVBoxLayout;
	lay->setMargin(0);
	lay->addWidget(make_filter_button_row());
	lay->addWidget(make_cart_button_row());
	newWnd->setLayout(lay);
	return newWnd;
}

QWidget* tema_lab10::make_filter_button_row()
{
	QWidget* filter_button_row = new QWidget;
	QHBoxLayout *filter_button_row_layout = new QHBoxLayout;
	filter_button_row_layout->setContentsMargins(0, 0, 0, 0);

	filter_button_row_layout->addWidget(filter_by_name_button);
	filter_button_row_layout->addWidget(filter_by_type_button);
	filter_button_row_layout->addWidget(filter_by_manufacturer_button);
	filter_button_row_layout->addWidget(cancel_button);
	cancel_button->setVisible(false);

	filter_button_row->setLayout(filter_button_row_layout);
	return filter_button_row;
}

QWidget* tema_lab10::make_right_pane()
{
	QWidget *right_pane = new QWidget;
	form = make_form();

	right_pane->setMaximumWidth(380);
	right_pane->setMinimumWidth(380);

	QGridLayout* right_pane_layout = new QGridLayout;
	
	right_pane_layout->addWidget(form);

	right_pane_layout->addWidget(make_add_upd_button_row());
	right_pane_layout->addWidget(new QWidget());


	right_pane_buttons_widget = make_right_pane_buttons_widget();
	right_pane_layout->addWidget(make_right_pane_buttons_widget());

	right_pane_layout->setRowStretch(2, 0);
	
	right_pane->setLayout(right_pane_layout);

	return right_pane;
}

QWidget* tema_lab10::make_table_button_row()
{
	QWidget* table_button_row = new QWidget;
	QHBoxLayout *table_button_row_layout = new QHBoxLayout;
	table_button_row_layout->setContentsMargins(0, 0, 0, 0);

	table_button_row_layout->addWidget(add_to_cart_button);
	table_button_row_layout->addWidget(remove_button);
	table_button_row_layout->addWidget(sort_by_name_button);
	table_button_row_layout->addWidget(sort_by_price_button);


	table_button_row->setLayout(table_button_row_layout);
	return table_button_row;
}

QWidget* tema_lab10::make_left_pane()
{
	QWidget *left_pane = new QWidget;
	QVBoxLayout* left_pane_layout = new QVBoxLayout;

	prepare_list();
	left_pane_layout->addWidget(list);
	left_pane_layout->addWidget(make_table_button_row());

	left_pane->setLayout(left_pane_layout);
	return left_pane;
}

void tema_lab10::prepare_list()
{
	list->setColumnCount(4);
	list->setShowGrid(true);
	
	QStringList header;
	header << "Name" << "Type" << "Price" << "Manufacturer";
	list->setHorizontalHeaderLabels(header);
	list->verticalHeader()->setVisible(false);
	list->setEditTriggers(QAbstractItemView::NoEditTriggers);
	list->setSelectionBehavior(QAbstractItemView::SelectRows);
	list->setSelectionMode(QAbstractItemView::SingleSelection);
}

void tema_lab10::make_menu_bar()
{
	QMenu* file_menu = menuBar()->addMenu("&File");
	QMenu* edit_menu = menuBar()->addMenu("&Edit");
	QMenu* help_menu = menuBar()->addMenu("&Help");

	open_action = new QAction("&Open", this);
	open_action->setShortcut(QKeySequence("Ctrl+O"));

	save_action = new QAction("&Save", this);
	save_action->setShortcut(QKeySequence("Ctrl+S"));

	save_as_action = new QAction("Save &As...", this);
	//save_as_action->setShortcut(QKeySequence("Ctrl+Alt+S"));
	
	undo_action = new QAction("&Undo", this);
	undo_action->setShortcut(QKeySequence("Ctrl+Z"));

	exit_action = new QAction("E&xit", this);
	about_action = new QAction("&About", this);

	file_menu->addAction(open_action);
	file_menu->addAction(save_action);
	file_menu->addAction(save_as_action);
	file_menu->addSeparator();
	file_menu->addAction(exit_action);

	edit_menu->addAction(undo_action);
	help_menu->addAction(about_action);
}

void tema_lab10::prepare_elements()
{	
	QWidget *newWnd = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
	
	layout->addWidget(make_left_pane());
	layout->addWidget(make_right_pane());
	
	make_menu_bar(); 
	newWnd->setLayout(layout);
	this->setCentralWidget(newWnd);
	
}

void tema_lab10::initialize_elements()
{
	QObject::connect(add_button, SIGNAL(clicked()), this, SLOT(func_add()));
	QObject::connect(remove_button, SIGNAL(clicked()), this, SLOT(func_remove()));
	QObject::connect(update_button, SIGNAL(clicked()), this, SLOT(func_upd()));
	QObject::connect(exit_action, SIGNAL(triggered()), this, SLOT(func_exit()));
	QObject::connect(about_action, SIGNAL(triggered()), this, SLOT(func_about()));
	QObject::connect(open_action, SIGNAL(triggered()), this, SLOT(func_load_file()));
	QObject::connect(save_action, SIGNAL(triggered()), this, SLOT(func_save_file()));
	QObject::connect(undo_action, SIGNAL(triggered()), this, SLOT(func_undo()));
	QObject::connect(filter_by_type_button, SIGNAL(clicked()), this, SLOT(func_filter_by_type()));
	QObject::connect(filter_by_name_button, SIGNAL(clicked()), this, SLOT(func_filter_by_name()));
	QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(func_cancel()));
	QObject::connect(cart_button, SIGNAL(clicked()), this, SLOT(func_cos()));
	QObject::connect(filter_by_manufacturer_button, SIGNAL(clicked()), this, SLOT(func_filter_by_manufacturer()));
	QObject::connect(save_as_action, SIGNAL(triggered()), this, SLOT(func_save_as_file()));
	QObject::connect(add_to_cart_button, SIGNAL(clicked()), this, SLOT(func_add_to_cart()));
}

void tema_lab10::func_add_to_cart()
{
	try {
		//produs pr = produs_dialog::update_form("");
		for (int i = 0; i < list->rowCount(); i++)
		{
			if (list->item(i, 0)->isSelected())
			{
				//qDebug() << list->item(i, 0)->text();

				serv_cos.adauga_incos(list->item(i,0)->text().toStdString());
			}
		}
	}
	//catch (produs_dialog_error&) {}
	catch (std::exception& ex)
	{
		QMessageBox::warning(this, "Magazin", ex.what());
	}
}


void tema_lab10::func_add()
{
	std::string name = name_textbox->text().toStdString();
	std::string type = type_textbox->text().toStdString();
	float price = price_textbox->text().toFloat();
	std::string manufacturer = manufacturer_textbox->text().toStdString();

	try
	{
		srv.insert(name, type, price, manufacturer);
		/*if (!filter_mode)
			refresh_list();
		else*/
		produs prod = { name, type, price, manufacturer };
		{
			modified++;
			list->insertRow(list->rowCount());
			list->setItem(list->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(prod.get_nume())));
			list->setItem(list->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(prod.get_tip())));
			list->setItem(list->rowCount() - 1, 2, new QTableWidgetItem(QString::number(prod.get_pret())));
			list->setItem(list->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(prod.get_producator())));
			QColor* culoare = new QColor("yellow");
			list->item(list->rowCount() - 1, 0)->setBackgroundColor(*culoare);
			list->item(list->rowCount() - 1, 1)->setBackgroundColor(*culoare);
			list->item(list->rowCount() - 1, 2)->setBackgroundColor(*culoare);
			list->item(list->rowCount() - 1, 3)->setBackgroundColor(*culoare);
		}
	}
	catch (std::exception& exc)
	{
		QMessageBox::critical(this, "Error", exc.what());
	}
}

void tema_lab10::func_upd()
{
	bool ok = false;

	for (int i = 0; i < list->rowCount(); i++)
	{
		if (list->item(i, 0)->isSelected())
		{
			try
			{
				produs p;
				try { p = produs_dialog::update_form(list->item(i, 0)->text()); }
				catch (produs_dialog_error&) { continue; }

				srv.modifica(list->item(i, 0)->text().toStdString(), p.get_nume(), p.get_tip(), p.get_pret(), p.get_producator());
				{
					list->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.get_nume())));
					list->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.get_tip())));
					list->setItem(i, 2, new QTableWidgetItem(QString::number(p.get_pret())));
					list->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(p.get_producator())));
				}

				if (ok == false) modified++;
				ok = true;
				
			}
			catch (std::exception& exc)
			{
				QMessageBox::critical(this, "Error", exc.what());
			}
		}
	}
}

void tema_lab10::func_remove()
{
	//qDebug() << "M " << list->rowCount();
	bool ok = false;

	for (int i = 0; i < list->rowCount(); i++)
	{
		if (list->item(i, 0)->isSelected())
		{
			ok = true;
			auto nume = list->item(i, 0)->text().toStdString();
			try
			{
				modified++;
				srv.erase(nume);
				list->removeRow(i);
				i--;
				break;
			}
			catch (std::exception& exc)
			{
				qDebug() << exc.what() << "\n";
				QMessageBox::critical(this, "Error", "Elementul nu exista in fisier!");
			}
		}
	}
	/*if (ok)
	{
		refresh_list();
	}*/
}

void tema_lab10::func_exit()
{
	QApplication::quit();
}

void tema_lab10::func_undo()
{
	try 
	{
		srv.undo();
		if (modified > 0) modified--;
	}
	catch(std::exception&) {}
	refresh_list();
}

void tema_lab10::func_load_file()
{
	bool not_save = false;
	if (modified)
	{
		auto btn = QMessageBox::warning(this, "Magazin", "Do you want to save changes for " + filename + "?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel);
		if (btn == QMessageBox::Cancel)
		{
			return;
		}
		else if (btn == QMessageBox::Save)
		{
			func_save_file();
		}
		else if (btn == QMessageBox::Discard)
		{
			not_save = true;
		}
	}

	filter_mode = false;
	modified = false;
	filename = QFileDialog::getOpenFileName(this, tr("Open file"), "", "CSV Files (*.csv)");
	if (filename == "") return;
	//qDebug() << nume_fisier;
	srv.deschide_fisier(filename.toStdString(), false);
	this->setWindowTitle(filename + " - Magazin");
	refresh_list();
}

void tema_lab10::func_save_file()
{
	if (filename == "")
	{
		filename = QFileDialog::getSaveFileName(this, tr("Save file"), "", "CSV Files (*.csv);;All Files (*.*)");
	}
	if (filename == "") return;
	srv.salveaza_fisier(filename.toStdString());
	modified = 0;
	this->setWindowTitle(filename + " - Magazin");
}

void tema_lab10::func_save_as_file()
{
	bool is_fresh_file = false;
	if (filename == "") is_fresh_file = true;

	auto name_file = QFileDialog::getSaveFileName(this, tr("Save file"), "", "CSV Files (*.csv);;All Files (*.*)");
	if (name_file == "") return;
	srv.salveaza_fisier(name_file.toStdString());
	if (filename == "")
	{
		filename = name_file;
	}
	if (is_fresh_file)
	{
		this->setWindowTitle(filename + " - Magazin");
		refresh_list();
	}
}

void tema_lab10::func_sort()
{
}

void tema_lab10::func_filter_by_type()
{
	auto str = QInputDialog::getText(this, "Filter", "Name");
//	qDebug() << str;
	if (str != "")
	{
		filter_mode = true;
		auto prd = srv.filtrare("tip", str.toStdString());
		refresh_list(true, prd);
		cancel_button->setVisible(true);
		filter_by_manufacturer_button->setVisible(false);
		filter_by_type_button->setVisible(false);
		filter_by_name_button->setVisible(false);
		sort_by_name_button->setVisible(false);
		sort_by_price_button->setVisible(false);
	}
	
}

void tema_lab10::func_filter_by_name()
{
	auto str = QInputDialog::getText(this, "Filter", "Name");
	if (str != "")
	{
		filter_mode = true;
		auto prd = srv.filtrare("nume", str.toStdString());
		refresh_list(true, prd);
		cancel_button->setVisible(true);
		filter_by_manufacturer_button->setVisible(false);
		filter_by_type_button->setVisible(false);
		filter_by_name_button->setVisible(false);
		sort_by_name_button->setVisible(false);
		sort_by_price_button->setVisible(false);
	}
}

void tema_lab10::func_filter_by_manufacturer()
{
	auto str = QInputDialog::getText(this, "Filter", "Name");
	if (str != "")
	{
		filter_mode = true;
		auto prd = srv.filtrare("producator", str.toStdString());
		refresh_list(true, prd);
		cancel_button->setVisible(true);
		filter_by_manufacturer_button->setVisible(false);
		filter_by_type_button->setVisible(false);
		filter_by_name_button->setVisible(false);
		sort_by_name_button->setVisible(false);
		sort_by_price_button->setVisible(false);
	}
}


void tema_lab10::func_cos()
{
	CosGui* fereastra = new CosGui{ serv_cos };
	fereastra->show();
}

void tema_lab10::func_cancel()
{
	filter_by_manufacturer_button->setVisible(true);
	filter_by_type_button->setVisible(true);
	filter_by_name_button->setVisible(true);
	sort_by_name_button->setVisible(true);
	sort_by_price_button->setVisible(true);
	filter_mode = false;
	cancel_button->setVisible(false);
	refresh_list();
}

void tema_lab10::func_about()
{
	QMessageBox::about(this, "About", "Acesta este o tema la OOP in cinstea profesorului Mircea Ioan-Gabriel.\n\nToate drepturile sunt rezervate lui Haja Florin-Gabriel.");
}



void tema_lab10::refresh_list(bool external, std::vector<produs> lst)
{
	list->setRowCount(0);
	std::vector<produs> k = srv.toate();
	if (external) k = lst;
	//auto produse = srv.toate();
	for (auto prod : k)
	{
		list->insertRow(list->rowCount());
		list->setItem(list->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(prod.get_nume())));
		list->setItem(list->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(prod.get_tip())));
		list->setItem(list->rowCount() - 1, 2, new QTableWidgetItem(QString::number(prod.get_pret())));
		list->setItem(list->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(prod.get_producator())));
	}
}

bool tema_lab10::save_dialog()
{
	return false;
}

void tema_lab10::closeEvent(QCloseEvent* ev)
{
	if (modified)
	{
		auto btn = QMessageBox::warning(this, "Magazin", "Do you want to save changes for " + filename + "?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Cancel);
		if (btn == QMessageBox::Cancel)
		{
			ev->ignore();
		}
		else if (btn == QMessageBox::Save)
		{
			func_save_file();
			ev->accept();
		}
		else if (btn == QMessageBox::Discard)
		{
			ev->accept();
		}
	}
}
