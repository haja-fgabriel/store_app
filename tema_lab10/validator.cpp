#include "validator.h"

void valideaza(const std::string &nume, const std::string &tip, const float &pret, const std::string &producator)
{
	(void)tip;
	(void)producator;
	std::string errors;
	if (nume.find_first_of('"') != std::string::npos)
	{
		errors += "Numele contine ghilimele\n";
	}
	if (nume.find_first_of(',') != std::string::npos)
	{
		errors += "Numele contine virgula\n";
	}
	if (tip.find_first_of('"') != std::string::npos)
	{
		errors += "Tipul contine ghilimele\n";
	}
	if (tip.find_first_of(',') != std::string::npos)
	{
		errors += "Tipul contine virgula\n";
	}
	if (producator.find_first_of('"') != std::string::npos)
	{
		errors += "Producatorul contine ghilimele\n";
	}
	if (producator.find_first_of(',') != std::string::npos)
	{
		errors += "Producatorul contine virgula\n";
	}

	if (pret < 0)
	{
		errors += "Pret mai mic decat 0\n";
	}
	if (errors.length() > 0)
	{
		throw std::exception(errors.c_str());
	}
}