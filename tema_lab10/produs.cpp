#include "produs.h"
#include <cstdio>
#include <cstring>
#include <cctype>

int __nr_instantieri;

void increment_inst() { __nr_instantieri++; }
int get_inst() { return __nr_instantieri; }

std::istream & operator>>(std::istream& s, produs & prd)
{
	std::string tmp;
	char cache;
	int ind = 1;
	while (s.get(cache))
	{
		if (cache == '\n' || isspace(cache))
		{
			prd.set_producator(tmp);
			break;
		}
		if (cache == '\r') continue;	// fisierele scrise pe Windows contin la sfarsitul
										// fiecarui rand si \r, si \n
		if (cache == ',')
		{
			switch (ind)
			{
			case 1: prd.set_nume(tmp);			break;
			case 2: prd.set_tip(tmp);			break;
			case 3: prd.set_pret(stof(tmp));	break;
			}
			tmp.clear();
			ind++; continue;
		}
		tmp += cache;

	}
	return s;
}

std::ostream & operator<<(std::ostream & s, produs prd)
{
	s << prd.get_nume() << ',' << prd.get_tip() << ',' << prd.get_pret() << ',' << prd.get_producator();
	return s;
}

std::string produs::get_nume() const
{
	return nume;
}

std::string produs::get_tip() const
{
	return tip;
}

std::string produs::get_producator() const
{
	return producator;
}

float produs::get_pret() const
{
	return this->pret;
}

std::string produs::get_member_names() const
{
	return std::string("Nume,Tip,Pret,Producator");
}

std::string produs::get_pret_as_string(int &lng) const
{
	char pret_str[12];
	sprintf_s(pret_str, 12, "%.2f", pret);
	lng = strlen(pret_str);
	return std::string{ pret_str };
}

bool produs::operator==(const produs & other) const
{
	return nume == other.get_nume();
}

void produs::set_nume(const std::string & new_nume)
{
	this->nume = new_nume;
}

void produs::set_tip(const std::string & new_tip)
{
	this->tip = new_tip;
}

void produs::set_producator(const std::string & new_prod)
{
	this->producator = new_prod;
}

void produs::set_pret(const float & k)
{
	this->pret = k;
}

produs & produs::operator=(const produs & pr)
{
	increment_inst();
	produs new_pr;
	if (&pr != this)
	{
		nume = pr.get_nume();
		tip = pr.get_tip();
		pret = pr.get_pret();
		producator = pr.get_producator();
	}
	return *this;
}

produs::produs(const std::string & nume, const std::string tip, const float & pret, const std::string & producator)
{
	increment_inst();
	this->nume = nume;
	this->tip = tip;
	this->pret = pret;
	this->producator = producator;
}

produs::~produs()
{

}
