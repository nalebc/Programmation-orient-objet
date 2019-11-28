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
	double revenu = 0;
	for (auto it : conteneur_) {
		vector<Billet*> b = it.second->getBillets();
		for_each(b.begin(), b.end(), [&revenu](const Billet* billet) { revenu += billet->getPrix(); });
	}
	return revenu;
}

int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{
	int nbBilletsSolde = 0;
	for (auto it : conteneur_) {
		vector<Billet*> b = it.second->getBillets();
		for_each(b.begin(), b.end(), [&nbBilletsSolde](Billet* billet) { if (dynamic_cast<Solde*>(billet)) nbBilletsSolde++; });
	}
	return nbBilletsSolde;
}

Billet * GestionnaireMembres::getBilletMin(  string nomMembre) const
{
	vector<Billet*> b = conteneur_.at(nomMembre)->getBillets();
	return *(min_element(b.begin(), b.end(), [](const Billet* b1,const  Billet* b2) { return b1->getPrix() < b2->getPrix(); }));
}

Billet * GestionnaireMembres::getBilletMax(string nomMembre) const
{
	vector<Billet*> b = conteneur_.at(nomMembre)->getBillets();
	return *(max_element(b.begin(), b.end(), [](const Billet* b1,const Billet* b2) {return b1->getPrix() < b2->getPrix(); }));
}



vector<Billet*> GestionnaireMembres::trouverBilletParIntervallle(Membre * membre, double prixInf, double prixSup) const
{
	vector<Billet*> billetTrouve;
	vector<Billet*> b = membre->getBillets();
	copy_if(b.begin(), b.end(), back_inserter(billetTrouve), [prixInf,prixSup]( Billet* b) {return IntervallePrixBillet(prixInf, prixSup)(b); });
	return billetTrouve;
	

}



void GestionnaireMembres::afficher(ostream& o) const
{
	//TODO
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for (auto it : conteneur_)
		it.second->afficher(o);

}
