/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "GestionnaireMembres.h"
#include <numeric>
#include<algorithm>


void GestionnaireMembres::assignerBillet(Billet* billet, const string& nomMembre, int rabaisCoupon)
{
	Membre* membre = conteneur_[nomMembre];

	if (membre == nullptr) {
		delete billet;
		return;
	}

	double prix = billet->getPrix();

	if (auto solde = dynamic_cast<Solde*>(billet)) {
		prix = solde->getPrixBase();
	}

	
	prix -= rabaisCoupon;
	

	if (auto membrePremium = dynamic_cast<MembrePremium*>(membre)) {
		double rabais = 0.005 * membrePremium->getpointsCumulee() / 1000;
		if (rabais > 0.1)
			rabais = 0.1;

		prix *= (1 - rabais);
	}

	billet->setPrix(prix);
	membre->ajouterBillet(billet);
}



double GestionnaireMembres::calculerRevenu() const
{
	//TODO
	double revenu = 0;
	for (auto it : conteneur_) {
		vector<Billet*> b = it.second->getBillets();
		for_each(b.begin(), b.end(), [&revenu](Billet* billet) { revenu += billet->getPrix(); });
	}
	return revenu;
}

int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{
	
//TODO
	int nbBilletsSolde = 0;
	for (auto it : conteneur_) {
		vector<Billet*> b = it.second->getBillets();
		for_each(b.begin(), b.end(), [&nbBilletsSolde](Billet* billet) { if (dynamic_cast<Solde*>(billet)) nbBilletsSolde++; });
	}
	return nbBilletsSolde;
}

Billet * GestionnaireMembres::getBilletMin(  string nomMembre) const
{
	
	Membre* membre = conteneur_.at(nomMembre);
	vector<Billet*> b = membre->getBillets();
	auto compare = [](Billet* b1, Billet* b2) { return b1->getPrix() < b2->getPrix(); };
	return *(min_element(b.begin(), b.end(), compare));
	
}

Billet * GestionnaireMembres::getBilletMax(string nomMembre) const
{
	Membre* membre = conteneur_.at(nomMembre);
	vector<Billet*> b = membre->getBillets();
	auto compare = [](Billet* b1, Billet* b2) {return b1->getPrix() < b2->getPrix(); };
	return *(max_element(b.begin(), b.end(), compare));

	
}



vector<Billet*> GestionnaireMembres::trouverBilletParIntervallle(Membre * membre, double prixInf, double prixSup) const
{
	vector<Billet*> billetTrouve;
	vector<Billet*> b = membre->getBillets();
	copy_if(b.begin(), b.end(), back_inserter(billetTrouve), [prixInf,prixSup](Billet* b) {return IntervallePrixBillet(prixInf, prixSup)(b); });
	return billetTrouve;
	

}



void GestionnaireMembres::afficher(ostream& o) const
{
	//TODO
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++)
		it->second->afficher(o);

/*
	for (size_t i =0 ; i<membres_.size() ; ++i) {
		membres[i]->afficher(o);
	}*/
}
