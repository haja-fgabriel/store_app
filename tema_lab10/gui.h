#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QFormLayout>
#include <QTableWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QToolbar>
#include <QAction>
#include <QString>

#include "service.h"
#include "ServiceCos.h"

#include "ui_tema_lab10.h"

class tema_lab10 : public QMainWindow
{
	Q_OBJECT

public:
	tema_lab10(service& srv, service_cos& srv_cos, QWidget *parent = Q_NULLPTR);

private slots:
	void func_add_to_cart();
	void func_add();
	void func_upd();
	void func_remove();
	void func_exit();
	void func_undo();
	void func_load_file();
	void func_save_file();
	void func_save_as_file();
	void func_sort();
	void func_filter_by_type();
	void func_filter_by_name();
	void func_filter_by_manufacturer();
	void func_cos();
	void func_cancel();
	void func_about();


private:
	bool filter_mode = false;
	int modified = 0;
	service& srv;
	service* srv_adr;
	service_cos& serv_cos;
	QString filename;

	QToolBar* toolbar = new QToolBar;

	QLineEdit* name_textbox = new QLineEdit;
	QLineEdit* type_textbox = new QLineEdit;
	QLineEdit* price_textbox = new QLineEdit;
	QLineEdit* manufacturer_textbox = new QLineEdit;

	QTableWidget *list = new QTableWidget;

	QWidget *wnd = new QWidget;
	QAction* open_action;
	QAction* save_action;
	QAction* save_as_action;
	QAction* exit_action;
	QAction* undo_action;
	QAction* about_action;

	QPushButton *cancel_button = new QPushButton("&Cancel");
	QPushButton *add_button = new QPushButton("&Add");
	QPushButton *update_button = new QPushButton("&Update");
	QPushButton *remove_button = new QPushButton("&Remove");
	QPushButton *sort_by_name_button = new QPushButton("Sort by &name");
	QPushButton *sort_by_price_button = new QPushButton("Sort by &price");
	QPushButton *filter_by_name_button = new QPushButton("&Filter by name");
	QPushButton *filter_by_type_button = new QPushButton("Filter by &type");
	QPushButton *filter_by_manufacturer_button = new QPushButton("Filter by &manufacturer");
	QPushButton *cart_button = new QPushButton("&Cart");
	QPushButton *cart_read_only_button = new QPushButton("&Cart (read-only)");
	QPushButton *add_to_cart_button = new QPushButton("&Add to cart");

	//QWidget *add_upd_button_row;
	QWidget *form;
	QWidget *right_pane_buttons_widget;
		
private:

	void refresh_list(bool external = false, std::vector<produs> lst = {});
	bool save_dialog();
	void closeEvent(QCloseEvent * ev);
	void make_menu_bar();
	QWidget* make_left_pane();
	QWidget* make_right_pane();
	QWidget* make_form();
	QWidget* make_add_upd_button_row();
	QWidget* make_cart_button_row();
	QWidget* make_right_pane_buttons_widget();
	QWidget* make_table_button_row();
	QWidget* make_filter_button_row();

	void prepare_list();
	void prepare_elements();
	void initialize_elements();

	Ui::tema_lab10Class ui;
};


