#pragma once
#include "produs.h"
#include "repository.h"
#include <vector>
#include <string>
#include <fstream>

class cos_cumparaturi
{
private:
	std::string nume_fisier;
	std::vector<produs*> elemente;
	repository<produs> &repo;

	produs* genereaza_produs();
	void citeste_fisier();
public:
	void clear();
	cos_cumparaturi(const std::string& nume, repository<produs>& elemente_repo, const int &k = 0);
	cos_cumparaturi(repository<produs>& elemente_repo, const int &k = 0);
	cos_cumparaturi(const std::string & nume, const cos_cumparaturi& cos);
	cos_cumparaturi& operator=(const cos_cumparaturi& alt_cos);
	cos_cumparaturi() = default;
	//cos_cumparaturi operator=(const cos_cumparaturi& cos);

	std::string get_nume_fisier();
	float pret_total() const;
	int size() const;
	bool adauga(const std::string&);
	void genereaza(const int &k);
	void salveaza();
	const std::vector<produs*>& get_all() const;
	~cos_cumparaturi();
};

