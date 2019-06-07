#include <cassert>
#include "tests.h"
#include "produs.h"
#include "repository.h"
#include "service.h"
#include "Lista.h"
#include "Cos.h"
#include "ServiceCos.h"
#include "Observable.h"
#include "Observer.h"

// avem nevoie de o functie de stergere a fisierului de test, DeleteFileA
#include "Windows.h"

void test_domain()
{
	produs prod( "iPhone", "telefon", 4199, "Apple" );
	produs prod2 = prod;
	std::string nume = prod2.get_nume();
	nume[0] = 'e';
	assert(prod2.get_nume() == prod.get_nume());
	assert(prod2.get_tip() == prod.get_tip());
	assert(prod2.get_producator() == prod.get_producator());
	assert(prod2.get_pret() == prod.get_pret());
	prod.set_producator("Momo");
	prod.set_nume("SteerPower5");
	prod.set_tip("volan");
	prod.set_pret(2100);
	int garbage;
	garbage = 2;
	assert(prod.get_pret_as_string(garbage) == "2100.00" && garbage == 7);
	assert(prod2.get_producator() != prod.get_producator());
	assert(prod2.get_pret() != prod.get_pret());
	assert(prod2.get_nume() != prod.get_nume());
	assert(prod2.get_tip() != prod.get_tip());
	get_inst();
}

void test_repo()
{
	DeleteFileA("test_produse.csv");
	DeleteFileA("test_produse2.csv");
	repository<produs> repo{ "test_produse.csv" };

	produs tel1("wrx sti", "masina", 60000, "subaru" );
	repo.insert(tel1);
	assert(repo.cauta(tel1) == true);
	try { repo.insert(tel1); }
	catch(std::exception&) { assert(true); }
	repo.elimina(tel1);
	assert(repo.cauta(tel1) == false);
	try { repo.elimina(tel1); }
	catch (std::exception&) { assert(true); }
	try { repo.modifica(tel1, { "206", "masina", 19000, "peugeot" }); }
	catch (std::exception&) { assert(true); }
	repo.insert(tel1);
	repo.modifica(tel1, { "206", "masina", 19000, "peugeot" });
	std::vector<produs> vec_nou = repo.get_all();
	vec_nou[0] = { "adas", "vibrator", 1, "vibroMAX" };
	assert(repo.cauta({ "adas", "vibrator", 1, "vibroMAX" }) == false);

	repo.set_nume_fisier("test_produse2.csv");
	repo.insert(tel1);
	assert(repo.size() == 1);
}

void test_serv()
{
	DeleteFileA("test_produse.csv");
	DeleteFileA("test_produse2.csv");
	repository<produs> repo{ "test_produse.csv" };
	cos_cumparaturi c{ "test_cos.csv", repo };
	service_cos sc{ c };
	service serv{ repo, sc };
	try { serv.insert("\"florin,", "\"baiat,", -1, "\"haja,"); }
	catch(std::exception&){}
	try { serv.undo(); }
	catch(std::exception&) {}
	serv.insert("florin", "baiat", 0, "haja");
	
	produs p("florin", "baiat", 0, "haja");
	actiune_undo a{ repo, p };
	a.do_undo();

	serv.modifica("florin", "manu", "k", (float)11.99, "drag");
	serv.undo();
	
	try { serv.insert("florin", "baiat", 0, "haja"); assert(false); }
	catch(std::exception&){}
	try { serv.insert("f", "t", -111, "h"); assert(false); }
	catch(std::exception&){ assert(true); }
	serv.erase("florin");
	serv.undo();
	assert(serv.toate().size() == 1);
	serv.erase("florin");
	try { serv.erase("florin");  assert(false); }
	catch (std::exception&) { assert(true); }
	assert(serv.cauta("florin") == false);
	try  { serv.modifica("florin", "gabriel", "nustiu", 0, "m"); }
	catch (std::exception&) { assert(true); }
	try { serv.modifica("florin", "ionutz", "valorosu", -1, "linguraru"); }
	catch (std::exception&) { assert(true); }
	serv.insert("florin", "baiat", 0, "haja");


	
	serv.insert("costi", "barbat", 1, "momo");
	auto rez = serv.filtrare("nume", "florin");
	assert(rez.size() == 1 && rez[0] == produs("florin", "baiat", 0, "haja"));

	rez = serv.filtrare("nume", "ionut");
	assert(rez.size() == 0);

	rez = serv.filtrare("tip", "baiat");
	assert(rez.size() == 1 && rez[0] == produs("florin", "baiat", 0, "haja"));
	
	rez = serv.filtrare("pret", "0");
	assert(rez.size() == 1 && rez[0] == produs("florin", "baiat", 0, "haja"));

	rez = serv.filtrare("producator", "haja");
	assert(rez.size() == 1 && rez[0] == produs("florin", "baiat", 0, "haja"));

	rez = serv.filtrare("nume", "ionut");
	assert(rez.size() == 0);


	rez = serv.sortare("nume");
	assert(rez[0] == produs("costi", "barbat", 1, "momo") && rez[1] == produs("florin", "baiat", 0, "haja"));
	rez = serv.sortare("pret");
	assert(rez[0] == produs("florin", "baiat", 0, "haja") && rez[1] == produs("costi", "barbat", 1, "momo"));
	rez = serv.sortare("nume-tip");
	assert(rez[0] == produs("costi", "barbat", 1, "momo") && rez[1] == produs("florin", "baiat", 0, "haja"));
	rez = serv.toate();
	assert(rez[0] == produs("florin", "baiat", 0, "haja") && rez[1] == produs("costi", "barbat", 1, "momo"));
	serv.undo();
	assert(serv.toate().size() == 1);
	serv.salveaza_fisier("test_produse2.csv");
	serv.deschide_fisier("test_produse2.csv");
	assert(serv.toate().size() == 1);

	const service& srv2 = serv;
	service& srv3 = (service&) srv2;
	srv3.cauta("Eminam");
}

void test_list()
{
	my_own::list<int> lista;
	for (int i = 0; i < 200; i++)
	{
		lista.push_back(i);
	}

	my_own::list<int>::iterator it = lista.begin();
	my_own::list<int>::iterator it2 = it;
	assert(lista.size() == 200);
	for (int i = 0; i < 200; i++)
	{
		assert(*it2 == i);
		assert(*it == i);
		++it2;
		assert(it2 != it);
		it++;
	}
	assert(it.valid() == false);

	my_own::list<int> lista2 = lista, lista3 = lista, lista4;

	lista4.push_back(2);
	lista4.pop_front();
	assert(lista4.size() == 0);

	while (lista.empty() == 0)
	{
		lista.pop_front();
	}

	
	while (lista2.empty() == 0)
	{
		lista2.pop_back();
	}
	lista2.erase(lista2.begin());


	try
	{
		lista2.erase(lista2.end());
		it++; }
	catch (std::exception&)
	{
		assert(true);
	}
	try{
		*it;}
	catch (std::exception&)
	{
		assert(true);
	}
	try{
		++it;}
	catch (std::exception&)
	{
		assert(true);
	}
}


void test_cos()
{
	DeleteFileA("test_cos.csv");
	DeleteFileA("test_produse.csv");

	repository<produs> repo{ "test_produse.csv" };

	repo.insert({ "florin", "baiat", 0, "haja" });
	repo.insert({ "denis", "baiat", 9, "ivan" });
	repo.insert({ "denisa", "fata", 1, "raducu" });
	repo.insert({ "ion", "baiat", 21, "porcescu" });
	repo.insert({ "ionela", "fata", 20, "cadar" });
	auto copie_repo = repo.get_all();
	assert(repo.size() == 5);
	
	{
		cos_cumparaturi c{ "test_cos.csv", repo };
		assert(c.adauga("florin") == true);
		assert(c.adauga("denisa") == true);
		assert(c.adauga("denisa") == true);
		assert(c.adauga("nicolae") == false);

		assert(c.size() == 3);
		assert(c.pret_total() == 2);

		auto k = c.get_all();

		for (auto* pr : k)
		{
			(void*)pr;
			assert(find(copie_repo.begin(), copie_repo.end(), *pr) != copie_repo.end());
		}

		repo.modifica({ "ionela", "fata", 20, "cadar" }, { "daria", "fata", 19, "malaria" });
		copie_repo = repo.get_all();
		for (auto* pr : k)
		{
			(void*)pr;
			assert(find(copie_repo.begin(), copie_repo.end(), *pr) != copie_repo.end());
		}
	}
	
	{
		cos_cumparaturi c2{"test_cos.csv", repo,2 };
		assert(c2.size() == 5);
		auto k2 = c2.get_all();

		for (auto* pr : k2)
		{
			(void)pr;
			assert(find(copie_repo.begin(), copie_repo.end(), *pr) != copie_repo.end());
		}
		c2.clear();
		assert(c2.size() == 0);
	}
}

void test_serv_cos()
{
	DeleteFileA("test_produse.csv");
	DeleteFileA("test_cos.csv");

	repository<produs> repo{ "test_produse.csv" };

	repo.insert({ "florin", "baiat", 0, "haja" });
	repo.insert({ "denis", "baiat", 9, "ivan" });
	repo.insert({ "denisa", "fata", 1, "raducu" });
	repo.insert({ "ion", "baiat", 21, "porcescu" });
	repo.insert({ "ionela", "fata", 20, "cadar" });
	auto copie_repo = repo.get_all();
	assert(repo.size() == 5);

	{
		cos_cumparaturi c2{ "test_cos.csv", repo, 2 };
		assert(c2.size() == 2);
		auto k2 = c2.get_all();

		for (auto* pr : k2)
		{
			(void*)pr;
			assert(find(copie_repo.begin(), copie_repo.end(), *pr) != copie_repo.end());
		}

		service_cos srv{ c2 };
		srv.adauga_incos("ionela");
		srv.genereaza_cos(3);
		auto all = srv.get_cos(); 
		assert(all.size() == 3);
		assert(srv.goleste_cos() == 0);
		srv.salveaza_cos();
		srv.salveaza_cos("mancare.csv");
		try
		{
			srv.adauga_incos("mmm");		}
		catch(std::exception&){}
	}
	{
		cos_cumparaturi c3{ repo, 4 };
		assert(repo.size() >= 4);
		c3.clear();
	}

}

void test_all()
{
	test_domain();
	test_repo();
	test_serv();
	test_list();
	test_cos();
	test_serv_cos();
}