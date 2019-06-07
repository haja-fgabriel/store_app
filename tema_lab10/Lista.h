//list.h
# pragma once

#include <cstdlib>
#include <exception>



namespace my_own
{
	template<typename TElem>
	class list 
  {

	private:
		typedef struct _Nod
		{
			TElem element;
			struct _Nod* urmator;
			_Nod(TElem e) { this->element = e, this->urmator = NULL; }
			~_Nod() {}
		} Nod;

		Nod* primNod;
		Nod* ultimNod;

		int Marime;


	public:
		class iterator
		{
			friend class list;
		private:
			const list &lis;
			list::Nod* nodLista;
			iterator(const list& l, list::Nod* e) : lis{ l }, nodLista{ e } {};

		public:
			iterator() = default;
			iterator& operator=(const iterator& old_it);
			~iterator();
			TElem& operator*() const;
			bool valid() const;
			bool operator!=(const iterator& k) { return this->nodLista != k.nodLista; }
			iterator& operator++();
			iterator& operator++(int);
		};
		friend class list::iterator;

		list();
		list(const list& ls);
		list& operator=(const list& ls);
		~list();

		int size() const;
		bool empty() const;
		void clear();

		iterator begin() const;
		iterator end() const;

		void push_back(TElem e);
		void pop_front();
		void pop_back();
		TElem erase(iterator poz);
		TElem& element(iterator poz) const;
		iterator cauta(TElem e) const;

	};
};


#include "Lista.cpp"