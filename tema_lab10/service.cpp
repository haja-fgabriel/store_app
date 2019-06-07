#include "service.h"
#include "validator.h"
#include <algorithm>
#include <functional>

service::service(repository<produs> &repo_de_copiat, service_cos& cs) : repo{ repo_de_copiat }, s{ cs } {}

std::vector<produs> service::toate() const
{
	return repo.get_all();
}

void service::deschide_fisier(const std::string & nume, bool save)
{
	repo.set_nume_fisier(nume, save);
}

void service::salveaza_fisier(const std::string & nume)
{
	repo.salveaza(nume);
}

void service::insert(const std::string & nume, const std::string & tip, const float & pret, const std::string & producator)
{
	try { valideaza(nume, tip, pret, producator); }
	catch (std::exception&) { throw; }
	produs pr{ nume, tip, pret, producator };
	try{repo.insert(pr);
	undo_adauga* op = new undo_adauga(repo, pr);
		lista_operatii.push_back(op);}
	catch (std::exception&) { throw; }
}

void service::erase(const std::string & nume)
{
	try  { valideaza(nume, "a", 1, "a");  } catch (std::exception&) { throw; }
	if (repo.size() == 0)
	{
		throw std::exception("Lista este goala");
	}

	produs pr{ nume, "a", 1, "a" };

	auto v = repo.get_all();
	auto it = std::find(v.begin(), v.end(), pr);

	try{repo.elimina(pr); 
	undo_sterge* op = new undo_sterge(repo, *it);
		lista_operatii.push_back(op); } catch (std::exception&) { throw; }
	
}

void service::undo()
{
	if (lista_operatii.empty())
	{
		throw std::exception("Nu mai puteti face undo!");
	}
	lista_operatii.back()->do_undo();
	delete lista_operatii.back();
	lista_operatii.pop_back();
}

bool service::cauta(const std::string &nume)
{
	try  { valideaza(nume, "a", 1, "a"); }  catch (std::exception&) { throw; }

	return repo.cauta({ nume, "a",1,"a" });
}

void service::setCos(service_cos & srv)
{
	s = srv;
}

void service::notifyCos()
{
	s.notify();
}

void service::modifica(const std::string & nume, const std::string & new_nume, const std::string & new_tip, const float & new_pret, const std::string & new_producator)
{
	try  
	{  
		valideaza(nume, "a", 1, "a" ); 
		valideaza(new_nume, new_tip, new_pret, new_producator); } catch (std::exception&) { throw; }
	
	if (repo.size() == 0)
	{
		throw std::exception();
	}

	auto v = repo.get_all();

	produs pr{ nume, "a", 1, "a" };
	produs pr2{ new_nume, new_tip, new_pret, new_producator };
	auto it = std::find(v.begin(), v.end(), pr);

	try { repo.modifica(pr, pr2); 
	undo_modifica* op = new undo_modifica(repo, *it, pr2);
	lista_operatii.push_back(op);}
	catch (std::exception&) { throw; }  }


std::vector<produs> service::filtrare(const std::string &tip_filtru, const std::string &filtru)
{
	std::vector<produs> toate_prod = repo.get_all();
	std::vector<produs> produse;
	produse.resize(toate_prod.size());

	std::vector<produs>::iterator rez;

	if (tip_filtru == "nume")		rez = std::copy_if(toate_prod.begin(), toate_prod.end(), produse.begin(), [=](const produs& obj) {return obj.get_nume() == filtru; });
	else if (tip_filtru == "tip")	rez = std::copy_if(toate_prod.begin(), toate_prod.end(), produse.begin(), [=](const produs& obj) {return obj.get_tip() == filtru; });
	else if (tip_filtru == "pret")  rez = std::copy_if(toate_prod.begin(), toate_prod.end(), produse.begin(), [=](const produs& obj) {return obj.get_pret() == stof(filtru); });
	else if (tip_filtru == "producator") rez = std::copy_if(toate_prod.begin(), toate_prod.end(), produse.begin(), [=](const produs& obj) {return obj.get_producator() == filtru; });
	
	//if (rez!=NULL)
	produse.erase(rez, produse.end());

	return produse;
}

std::vector<produs> service::sortare(const std::string& tip_filtru)
{
	std::vector<produs> produse = repo.get_all();
	produs ceva;

	if (tip_filtru == "pret")
	{
		std::sort(produse.begin(), produse.end(), [](const produs &a, const produs &b) {return a.get_pret() < b.get_pret(); });
	}
	else if (tip_filtru == "nume")
	{
		std::sort(produse.begin(), produse.end(), [](const produs &a, const produs &b) {return a.get_nume() < b.get_nume(); });
	}
	else if (tip_filtru == "nume-tip" || tip_filtru == "nume_tip")
	{
		std::sort(
			produse.begin(), produse.end(), [](const produs &a, const produs &b) {
										        return a.get_nume() < b.get_nume() ||
												       a.get_nume() == b.get_nume() && a.get_tip() < b.get_tip(); 
											}
		);
	}
	return produse;
}

service::~service()
{
	for (auto* k : lista_operatii)
	{
		delete k;
	}
}

service & service::operator=(const service & srv) 
{
	(void)srv;
	return *this;
}
