#pragma once
#include "repository.h"
#include <string>
#include <exception>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "produs.h"
#include "undo.h"
#include "ServiceCos.h"

class produs;

class service
{
	friend class produs;
private:
	repository<produs> &repo;
	std::vector<actiune_undo*> lista_operatii;
	service_cos& s;

public:
	service(repository<produs> &, service_cos& cs);
	service() = default;
	~service();

	service& operator=(const service& srv); 

	void deschide_fisier(const std::string& nume, bool ok = true);
	void salveaza_fisier(const std::string& nume = "");
	void insert(const std::string &nume, const std::string &tip, const float &pret, const std::string &producator);
	void erase(const std::string &nume);
	void modifica(const std::string &nume, const std::string &new_nume, const std::string &tip, const float &pret, const std::string &producator);
	bool cauta(const std::string & nume);

	void setCos(service_cos& srv);

	void notifyCos();

	void undo();

	std::vector<produs> filtrare(const std::string & tip_filtru, const std::string & filtru);
	std::vector<produs> sortare(const std::string & filtru);
	std::vector<produs> toate() const;

};
