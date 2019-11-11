/********************************************
* Titre: Travail pratique #5 - membre.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "membre.h"

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
	transform(membre.billets_.begin(), membre.billets_.end(), billets_.begin(), [](const Billet*  billet) -> Billet* {  return billet->clone(); });
}
//todo
Membre::~Membre()
{
	for (auto it = billets_.begin(); it != billets_.end(); it++) {
		delete *it;
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

vector<Billet*>::iterator Membre::trouverBillet(const string & pnr)
{

	return find_if(billets_.begin(), billets_.end(), [pnr](const Billet* billet) {return pnr == billet->getPnr(); });
}



//todo
void Membre::utiliserBillet(const string& pnr)
{

	auto it = trouverBillet(pnr);
	if( *it == nullptr) {
		cout << "Le billet n'est pas trouve" << endl;
		return;
	}
	if (auto flightPass = dynamic_cast<FlightPass*>(*it)) {
		flightPass->decrementeNbUtilisations();
		if (flightPass->getNbUtilisationsRestante() > 0) {
			return;
		}
	}
	billets_.erase(it);	
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
		for_each(billets_.begin(), billets_.end(), [](Billet* ptr) { delete ptr; });
		billets_.clear();
		copy(membre.billets_.begin(), membre.billets_.end(), billets_.begin());
	}
	return *this;
}


//todo
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	copy(billets_.begin(), billets_.end(), ostream_iterator<Billet*>(o, ""));
	
}