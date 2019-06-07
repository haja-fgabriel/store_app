#include "Cos.h"
#include <ctime>
#include <algorithm>
#include <iostream>

cos_cumparaturi::cos_cumparaturi(const std::string& nume, repository<produs>& elemente_repo, const int &nr_elem) : nume_fisier{ nume }, repo{elemente_repo}
{
	citeste_fisier();
	genereaza(nr_elem);
}

cos_cumparaturi::cos_cumparaturi(const std::string & nume, const cos_cumparaturi & cos) : nume_fisier{ nume }, elemente{ cos.elemente }, repo{ cos.repo } {}

cos_cumparaturi & cos_cumparaturi::operator=(const cos_cumparaturi & alt_cos)
{
	nume_fisier = alt_cos.nume_fisier;
	elemente = alt_cos.elemente;
	repo = alt_cos.repo;
	return *this;
}

cos_cumparaturi::cos_cumparaturi(repository<produs>& elemente_repo, const int & nr_elem) : nume_fisier {"cos_cumparaturi.csv"}, repo{elemente_repo}
{
	citeste_fisier();
	srand((unsigned int)time(NULL));
	genereaza(nr_elem);
}

cos_cumparaturi::~cos_cumparaturi()
{
	salveaza();
}

void cos_cumparaturi::citeste_fisier()
{
	
	produs prd;
	std::ifstream f(nume_fisier);

	char lin[30];
	f.getline(lin, 30);

	while (f >> prd)
	{
		for (int i = 0; i < repo.size(); i++)
		{
			if (prd == repo[i])
			{
				elemente.push_back(&repo[i]);
				break;
			}
		}
	}
	f.close();
}

void cos_cumparaturi::salveaza()
{
	std::ofstream f(nume_fisier);
	f << "Nume,Tip,Pret,Producator" << std::endl;
	for (auto* prod : elemente)
	{
		f << *prod << std::endl;
	}
	f.close();
}

produs* cos_cumparaturi::genereaza_produs()
{
	int k = rand() % repo.size(); 
	produs* where = &repo[k];
	return where;
}

void cos_cumparaturi::clear()
{
	elemente.clear();
	salveaza();
}


std::string cos_cumparaturi::get_nume_fisier()
{
	return nume_fisier;
}

float cos_cumparaturi::pret_total() const
{
	float suma = 0;
	for (auto* it : elemente) 
	{
		suma += it->get_pret();
	}
	return suma;
}

int cos_cumparaturi::size() const
{
	return elemente.size();
}

bool cos_cumparaturi::adauga(const std::string& str)
{
	bool ok = false;
	for (int i = 0; i < repo.size(); i++)
	{
		if (repo[i].get_nume() == str)
		{
			ok = true;
			elemente.push_back(&repo[i]);
			break;
		}
	}
	return ok;
}

void cos_cumparaturi::genereaza(const int &nr_elem)
{
	if (repo.size() == 0) return;
	for (int i = 0; i < nr_elem; i++)
	{
		elemente.push_back(genereaza_produs());
	}
}

const std::vector<produs*>& cos_cumparaturi::get_all() const
{
	return elemente;
}


