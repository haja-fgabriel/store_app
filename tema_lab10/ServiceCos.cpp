#include "ServiceCos.h"



service_cos & service_cos::operator=(service_cos & ss)
{
	this->cos = ss.cos;
	return *this;
}

float service_cos::genereaza_cos(const int & k)
{
	cos.clear();
	cos.genereaza(k);
	notify();
	return cos.pret_total();
}

float service_cos::adauga_incos(const std::string & str)
{
	if (!cos.adauga(str))
	{
		throw std::exception("Produsul ales nu este in stoc!");
	}
	notify();
	return cos.pret_total();
}

float service_cos::salveaza_cos(std::string nume)
{
	if (nume != "" && nume != cos.get_nume_fisier())
	{
		cos_cumparaturi m{ nume, cos };	// in destructor este apelata functia de salvare
	}
	else
	{
		cos.salveaza();
	}
	return cos.pret_total();
}

float service_cos::goleste_cos()
{
	cos.clear();
	notify();
	return cos.pret_total();
}

const std::vector<produs*>& service_cos::get_cos() const
{
	return cos.get_all();
}

service_cos::~service_cos()
{
}
