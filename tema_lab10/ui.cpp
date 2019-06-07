#include "ui.h"



char meniu[] = (
	"Optiuni:\n  1. Adauga produs (nume, tip, pret, producator)\n"
	"  2. Elimina produs (nume)\n"
	"  3. Cauta produs (nume)\n"
	"  4. Modifica produs (nume, nume nou, tip nou, pret nou, producator nou)\n"
	"  5. Afiseaza produse\n"
	"  6. Filtreaza produse (nume, pret, producator)\n"
	"  7. Sortare produse (nume, pret, nume+tip)\n"
	"  8. Adauga produs in cos (nume)\n"
	"  9. Genereaza cos cu un (numar) dat de elemente\n"
	" 10. Goleste cos\n"
	" 11. Salveaza cosul in fisierul cu numele (nume)\n"
	" 12. Afiseaza cos\n"
	" 13. Undo pe lista de produse\n"
	" 14. Paraseste programul\nComanda: "
);

std::string ui::list_to_string(const std::vector<produs>& produse)
{
	std::string rez = "Nume         Tip         Pret        Producator\n";
	for (const auto& pr : produse)
	{
		std::string de_adaugat = pr.get_nume() + std::string(13 - pr.get_nume().length(), ' ');
		de_adaugat += pr.get_tip() + std::string(12 - pr.get_tip().length(), ' ');

		int ln;
		de_adaugat += pr.get_pret_as_string(ln);
		de_adaugat += std::string(12 - ln, ' ' );
		de_adaugat += pr.get_producator() + std::string(12 - pr.get_producator().length(), ' ');
		de_adaugat += '\n';
		rez += de_adaugat;
	}
	return rez;
}

std::string ui::list_to_string_cos(const std::vector<produs*>& produse)
{
	std::string rez = "Nume         Pret\n";
	for (const auto* pr : produse)
	{
		std::string de_adaugat = pr->get_nume() + std::string(13 - pr->get_nume().length(), ' ');

		int ln;
		de_adaugat += pr->get_pret_as_string(ln);
		de_adaugat += '\n';
		rez += de_adaugat;
	}
	return rez;
}

void ui::functie_adauga()
{
	std::string nume, tip, producator;
	float pret;
	std::cin >> nume >> tip >> pret >> producator;
	try { serv.insert(nume, tip, pret, producator); }
	catch (std::exception&) { throw; }
}

void ui::functie_modifica()
{
	std::string nume, nume_nou, tip_nou, producator_nou;
	float pret_nou;
	std::cin >> nume >> nume_nou >> tip_nou >> pret_nou >> producator_nou;
	try { serv.modifica(nume, nume_nou, tip_nou, pret_nou, producator_nou); }
	catch (std::exception&) { throw; }
}

void ui::functie_sterge()
{
	std::string nume;
	std::cin >> nume;
	try { serv.erase(nume); }
	catch (std::exception&) { throw; }
}

void ui::functie_cauta()
{
	std::string nume;
	std::cin >> nume;
	try 
	{ 
		if (serv.cauta(nume))
		{
			std::cout << nume << " exista in lista\n";
		}
		else
		{
			std::cout << nume << " nu exista in lista\n";
		}
	}
	catch (std::exception&) { throw; }
}

void ui::functie_filtrare()
{
	std::string tip_filtru, filtru;
	std::cin >> tip_filtru >> filtru;

	std::vector<produs> de_afisat = serv.filtrare(tip_filtru, filtru);
	std::cout << list_to_string(de_afisat) << '\n';
}

void ui::functie_afisare()
{
	std::cout << list_to_string(serv.toate()) << '\n';
}

void ui::functie_sortare()
{
	std::string tip_filtru;
	std::cin >> tip_filtru;
	
	std::cout << list_to_string(serv.sortare(tip_filtru)) << '\n';
}

void ui::functie_adauga_cos()
{
	std::string nume;
	std::cin >> nume;
	float p_total = srv_cos.adauga_incos(nume);
	std::cout << "Pret total cos: " << p_total << '\n';
}

void ui::functie_generare_cos()
{
	int k;
	std::cin >> k;
	float p_total = srv_cos.genereaza_cos(k);
	std::cout << "Pret total cos: " << p_total << '\n';
}

void ui::functie_golire_cos()
{
	srv_cos.goleste_cos();
}

void ui::functie_salvare_cos()
{
	std::string nume_fisier;
	std::cin >> nume_fisier;
	srv_cos.salveaza_cos(nume_fisier);
}

void ui::functie_afisare_cos()
{
	std::cout << list_to_string_cos(srv_cos.get_cos()) << '\n';
}

void ui::functie_undo()
{
	serv.undo();
}



ui::ui(service& srv, service_cos& c) : serv{ srv }, srv_cos{ c } {}

void ui::ruleaza()
{
	while (1)
	{
		std::cout << meniu << '\n'; 
		std::string comanda;
		std::cin >> comanda;
		try
		{
				 if (comanda == "1") functie_adauga();
			else if (comanda == "2") functie_sterge();  
			else if (comanda == "3") functie_cauta(); 
			else if (comanda == "4") functie_modifica();
			else if (comanda == "5") functie_afisare();
			else if (comanda == "6") functie_filtrare();
			else if (comanda == "7") functie_sortare();
			else if (comanda == "8") functie_adauga_cos();
			else if (comanda == "9") functie_generare_cos();
			else if (comanda == "10") functie_golire_cos();
			else if (comanda == "11") functie_salvare_cos();
			else if (comanda == "12") functie_afisare_cos();
			else if (comanda == "13") functie_undo();
			else if (comanda == "14") return;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
}

ui::~ui()
{
}
