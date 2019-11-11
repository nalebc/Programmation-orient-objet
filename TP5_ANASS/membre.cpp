/********************************************
* Titre: Travail pratique #5 - membre.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "membre.h"
#include <algorithm>

Membre::Membre() :
	nom_("")
{
}

Membre::Membre(const string& nom) :
	nom_(nom)
{
}

//todo
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	transform(membre.billets_.begin(), membre.billets_.end(), back_inserter(billets_), [](Billet* b) {return b->clone(); });
}

//todo
Membre::~Membre()
{
	for (size_t i = 0; i < billets_.size(); ++i) {
		delete billets_[i];
	}
}

string Membre::getNom() const
{
	return nom_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

vector<Billet*>::iterator Membre::trouverBillet(const string& pnr)
{
	auto iter=find_if(begin(billets_), end(billets_), [pnr](Billet* b) {return (b->getPnr() == pnr); });
	return iter;
}

//todo implemente trouverBillet() signature dans le .h

//todo
void Membre::utiliserBillet(const string& pnr)
{
	auto iter = trouverBillet(pnr);
	if (*iter==nullptr) {
		cout << "Le billet n'est pas trouve" << endl;
		return;
	}

	if (auto flightPass = dynamic_cast<FlightPass*>(*iter)) {
		flightPass->decrementeNbUtilisations();
		if (flightPass->getNbUtilisationsRestante() > 0) {
			return;
		}
	}
	billets_.erase(iter);
}

void Membre::ajouterBillet(Billet* billet)
{
	billet->setNomPassager(nom_);
	billets_.push_back(billet);
}

bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}


//todo
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;
		for (auto iter:billets_) {
			delete iter;
		}
		billets_.clear();
		transform(membre.billets_.begin(), membre.billets_.end(), back_inserter(billets_), [](Billet* b) {return b->clone();});
	}
	return *this;
}


//todo
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	copy(begin(billets_), end(billets_), ostream_iterator<Billet*>(o, " "));
}