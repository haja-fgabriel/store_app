#include "produs_dialog.h"
#include <QDialogButtonBox>

void produs_dialog::make_layout()
{ 
	QFormLayout *lay = new QFormLayout;
	//const QString st = ;
	lay->addRow(new QLabel("Please insert new parameters for product " + old_prd_name));
	lay->addRow("Name", name_textbox);
	lay->addRow("Type", type_textbox);
	lay->addRow("Price", price_textbox);
	lay->addRow("Manufacturer", manufacturer_textbox);

	QDialogButtonBox *b = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	QObject::connect(b, SIGNAL(accepted()), this, SLOT(accept()));
	QObject::connect(b, SIGNAL(rejected()), this, SLOT(reject()));
	lay->addRow(b);
	this->setLayout(lay);
}

produs_dialog::produs_dialog(QWidget* parent, const QString& title, const QString& old) : QDialog(parent)
{
	old_prd_name = old;
	this->setWindowTitle(title);
	this->setModal(true);
	make_layout();
}

produs produs_dialog::get_prod()
{
	std::string name = name_textbox->text().toStdString(); 
	std::string manuf = manufacturer_textbox->text().toStdString();
	std::string type = type_textbox->text().toStdString();
	float price = price_textbox->text().toFloat();

	return produs{ name, type, price, manuf };
}

produs produs_dialog::update_form(const QString& st)
{
	//QMessageBox::critical(this, "Magazin", "Merge");
	produs_dialog* dlg = new produs_dialog((QWidget*)nullptr, "Magazin", st);

	produs prd;
	if (dlg->exec() == QDialog::Accepted)
	{
		prd = dlg->get_prod();
	}
	else
	{
		throw produs_dialog_error();
	}

	return prd;
}