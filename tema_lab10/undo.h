#pragma once

#include "produs.h"
#include "repository.h"

class actiune_undo
{
private:
	produs pr;
	repository<produs>& repo;

public:
	virtual void do_undo();
	virtual ~actiune_undo() = default;

	produs get_produs() { return pr; };
	repository<produs>& get_repo() { return repo; }

	actiune_undo(repository<produs>& repo, const produs & pr);
};

class undo_adauga : public actiune_undo
{
public:
	undo_adauga(repository<produs>& repo, const produs & pr);
	~undo_adauga() = default;
	
	void do_undo();
};


class undo_sterge: public actiune_undo
{
public:
	undo_sterge(repository<produs>& repo, const produs & pr);
	~undo_sterge() = default;

	void do_undo();
};


class undo_modifica: public actiune_undo
{
private:
	produs pr2;
public:
	undo_modifica(repository<produs>& repo, const produs& pr, const produs& pr2);
	~undo_modifica() = default;

	void do_undo();
};
