#include "undo.h"

actiune_undo::actiune_undo(repository<produs>& ls, const produs& prd) : repo{ls}, pr{prd} {}
undo_adauga::undo_adauga(repository<produs>& repo, const produs & pr) : actiune_undo(repo, pr) {}
undo_sterge::undo_sterge(repository<produs>& repo, const produs & pr) : actiune_undo(repo, pr) {}
undo_modifica::undo_modifica(repository<produs>& repo, const produs & pr, const produs & prod2) :actiune_undo(repo, pr), pr2{prod2} {}

void actiune_undo::do_undo() {}

void undo_adauga::do_undo()
{
	get_repo().elimina(get_produs());
}


void undo_sterge::do_undo()
{
	get_repo().insert(get_produs());
}


void undo_modifica::do_undo()
{
	get_repo().modifica(pr2, get_produs());
}



