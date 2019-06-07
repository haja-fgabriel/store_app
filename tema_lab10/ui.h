#pragma once
#include <iostream>
#include <string>
#include <exception>
#include "service.h"
#include "repository.h"
#include "ServiceCos.h"

class ui
{
private:
	service& serv;
	service_cos& srv_cos;
	
	std::string list_to_string(const std::vector<produs>& produse);
	std::string list_to_string_cos(const std::vector<produs*>& produse);

	
	void functie_adauga();
	void functie_modifica();
	void functie_sterge();
	void functie_cauta();
	void functie_filtrare();
	void functie_afisare();
	void functie_sortare();
	void functie_adauga_cos();
	void functie_generare_cos();
	void functie_golire_cos();
	void functie_salvare_cos();
	void functie_afisare_cos();
	void functie_undo();

public:
	ui(service& srv, service_cos& c);
	void ruleaza();
	~ui();
};

