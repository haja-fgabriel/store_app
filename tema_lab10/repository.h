#pragma once

#include "produs.h"
#include <exception>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Windows.h"
#include <QDialog>


template <class T>
class repository
{
private:
	std::vector<T> lista_produse;
	std::string nume_fisier;

public:
	void set_nume_fisier(const std::string& f, bool save = true)
	{
		if (save) salveaza();
		lista_produse.clear();
		nume_fisier = f;
		citeste();
	}

	void citeste(std::string nume_f = "")
	{
		T prd;
		if (nume_f == "")
		{
			nume_f = nume_fisier;
		}
		std::ifstream f(nume_f);

		char first_line[30];
		f.getline(first_line, 30);

		while (f >> prd)
		{
			lista_produse.push_back(prd);
		}
		f.close();
	}
	void salveaza(std::string nume_f = "")
	{
		if (nume_f == "")
		{
			nume_f = nume_fisier;
		}
		std::ofstream f(nume_f);

		T m;
		f << m.get_member_names() << std::endl;
		
		for (auto prod : lista_produse)
		{
			f << prod << std::endl;
		}
		f.close();
	}


	T& operator[](int k) { return lista_produse[k]; }
	int size() { return lista_produse.size(); }

	std::vector<T> get_all() const
	{
		return lista_produse;
	}
	
	void insert(const T &p)
	{
		if (find(lista_produse.begin(), lista_produse.end(), p) == lista_produse.end())
		{
			lista_produse.push_back(p);
		}
		else
		{
			throw std::exception("Elementul deja exista!");
		}
	}

	void elimina(const T &p)
	{
		typename std::vector<T>::iterator it = find(lista_produse.begin(), lista_produse.end(), p);
		if (it == lista_produse.end())
		{
			throw std::exception("Elementul nu exista!");
		} 
		lista_produse.erase(it);
	}

	void modifica(const T &p_vechi, const T &p_nou)
	{
		typename std::vector<T>::iterator it = find(lista_produse.begin(), lista_produse.end(), p_vechi);
		if (it == lista_produse.end())
		{
			throw std::exception("Elementul nu exista!");
		}
		*it = p_nou;
	}

	bool cauta(const T &p)
	{
		return find(lista_produse.begin(), lista_produse.end(), p) != lista_produse.end();
	}

	repository(std::string nume = "") : nume_fisier{ nume } 
	{ 
		if (nume == "")
		{
			int cnt = 0;
			char name[35];
			sprintf_s(name,35, "produse.csv");
			std::ifstream test;
			test.open(name, std::ifstream::in);
			while (test.is_open())
			{
				test.close();
				if (cnt == 0)
				{
					sprintf_s(name,35, "produse_%d.csv", cnt);
				}
				cnt++;
				test.open(name, std::ifstream::in);
			} 
			nume = name;
		}
		citeste(); 
	}
	~repository() { salveaza(); }
};

