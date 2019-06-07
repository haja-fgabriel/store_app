#pragma once

#include "Lista.h"
#include <iostream>

#ifndef _LIST_IMPLEMENT
#define _LIST_IMPLEMENT

template<typename TElem>	my_own::list<TElem>::iterator::~iterator() {}

template<typename TElem>	typename my_own::list<TElem>::iterator& my_own::list<TElem>::iterator::operator=(const my_own::list<TElem>::iterator& old_it) 
{
	nodLista = old_it.nodLista;
	return *this;
}



template<typename TElem>	TElem& my_own::list<TElem>::iterator::operator*() const
{
	if (valid() == 0)
	{
		throw std::exception();
	}
	return this->nodLista->element; }

template<typename TElem>	inline bool my_own::list<TElem>::iterator::valid() const
{
	return nodLista != NULL;
}

template<typename TElem>	typename my_own::list<TElem>::iterator& my_own::list<TElem>::iterator::operator++()
{
	if (valid())
	{
		nodLista = nodLista->urmator;
	}
	else
	{
		throw std::exception();
	}
	return *this;
}

template<typename TElem>	typename my_own::list<TElem>::iterator& my_own::list<TElem>::iterator::operator++(int)
{
	if (valid())
	{
		nodLista = nodLista->urmator;
	}
	else
	{
		throw std::exception();
	}
	return *this;
}


template<typename TElem>	inline my_own::list<TElem>::list() { this->primNod = NULL; this->ultimNod = NULL; Marime = 0; }

template<typename TElem>	typename my_own::list<TElem>& my_own::list<TElem>::operator=(const my_own::list<TElem>& ls)
{
	clear();
	for (auto it : ls)
	{
		push_back(it);
	}
	return *this;
}

template<typename TElem>	my_own::list<TElem>::list(const my_own::list<TElem>& ls)
{
	//clear();
	primNod = ultimNod = NULL;
	Marime = 0;
	for (auto it : ls)
	{
		push_back(it);
	}
}



template<typename TElem>	int my_own::list<TElem>::size() const
{
	return this->Marime;
}

template<typename TElem>
bool my_own::list<TElem>::empty() const
{
	return Marime == 0;
}

template<typename TElem>	typename my_own::list<TElem>::iterator  my_own::list<TElem>::begin() const
{
	return list::iterator(*this, primNod);
}

template<typename TElem>	typename my_own::list<TElem>::iterator  my_own::list<TElem>::end() const
{
	Nod* n = ultimNod;
	if (n) n = n->urmator;
	return list::iterator(*this, n);
}


template<typename TElem>	typename TElem& my_own::list<TElem>::element(my_own::list<TElem>::iterator poz) const
{
	if (!poz.valid())
	{
		throw std::exception();
	}
	return poz.nodLista->element;
}


template<typename TElem>	void my_own::list<TElem>::push_back(TElem e)
{
	typename my_own::list<TElem>::Nod* nou = new Nod(e);
	if (this->primNod == NULL)
	{
		this->primNod = nou;
		this->ultimNod = nou;
	}
	else
	{
		this->ultimNod->urmator = nou;
		this->ultimNod = nou;
	}
	this->Marime++;
}
template<typename TElem>	TElem my_own::list<TElem>::erase(my_own::list<TElem>::iterator poz)
{
	if (empty() || poz.valid() == 0)
	{
		return { 0 };
	}
	
	list::Nod* inc = this->primNod;
	if (poz.nodLista != inc)
	{
		while (inc != NULL && inc->urmator != poz.nodLista)
		{
			inc = inc->urmator;
		}
	}
	
	inc->urmator = poz.nodLista->urmator;
	
	if (poz.nodLista == ultimNod) 
	{
		if (ultimNod != primNod)
		{
			ultimNod = inc;
		}
		else
		{ primNod = ultimNod = NULL; } }
	
	if (primNod != NULL && poz.nodLista == primNod)
	{
		primNod = primNod->urmator;
	}
	

	TElem retVal = poz.nodLista->element;
	this->Marime--;

	delete poz.nodLista;
	return retVal;
}

template<typename TElem>	void my_own::list<TElem>::pop_back()
{
	erase({*this, ultimNod});
}

template<typename TElem>	void my_own::list<TElem>::pop_front()	{	erase(begin());	}

template<typename TElem>	typename my_own::list<TElem>::iterator   my_own::list<TElem>::cauta(TElem e) const
{
	list<TElem>::iterator inc(*this, primNod);
	while (inc.valid())
	{
		if (inc.element() == e)
		{
			return inc;
		}
		inc.urmator();
	}
	return list<TElem>::iterator(*this, NULL);
}

template<typename TElem>	void my_own::list<TElem>::clear()
{
	while (Marime > 0)
	{
		Nod* acestNod = primNod;
		primNod = acestNod->urmator;
		delete acestNod;
		Marime--;
	}
	primNod = ultimNod = NULL; 
}

template<typename TElem>	my_own::list<TElem>::~list()
{
	while (Marime > 0)
	{
		Nod* acestNod = primNod;
		primNod = acestNod->urmator;
		delete acestNod;
		Marime--; } }

#endif