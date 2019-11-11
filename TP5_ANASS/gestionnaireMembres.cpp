/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "GestionnaireMembres.h"
#include <numeric>
#include <algorithm>
using namespace std;

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
	for (auto iter:conteneur_)
	{	
		auto it = conteneur_;
		vector<Billet*> billet = iter.second->getBillets();
		for_each(begin(billet), end(billet), [&revenu](Billet* b)->void {revenu += b->getPrix(); });
		//revenu = accumulate(begin(billet), end(billet), 0, [](Billet* a, Billet* b)->double {return (a->getPrix()+b->getPrix());});
	}
	return revenu;
}

int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{
	//TODO
	int nbBilletsSolde = 0;
	for (auto iter : conteneur_)
	{
		vector<Billet*> billet = iter.second->getBillets();
		nbBilletsSolde += count_if(begin(billet), end(billet), [](Billet* b){return dynamic_cast<Solde*>(b);});
	}
	return nbBilletsSolde;
}

Billet* GestionnaireMembres::getBilletMin(string nomMembre) const
{
	auto b =conteneur_.find(nomMembre);
	vector<Billet*> billet = b->second->getBillets();
	//auto billetMin = (find_if(begin(billet), end(billet), [](Billet* a, Billet* b){return (a->getPrix()<b->getPrix());}));
	auto billetMin=(min_element(billet.begin(), billet.end(), [](Billet* b1, Billet* b2) { return b1->getPrix() < b2->getPrix(); }));
	return *billetMin;
}

Billet* GestionnaireMembres::getBilletMax(string nomMembre) const
{
	auto b = conteneur_.find(nomMembre);
	vector<Billet*> billet = b->second->getBillets();
	//auto billetMax = find_if(billet.begin(), billet.end(), [](Billet* a, Billet* b) {return a->getPrix() > b->getPrix(); });
	auto billetMax = (max_element(begin(billet), end(billet), [](Billet* b1, Billet* b2) { return b1->getPrix() < b2->getPrix();}));
	return *billetMax;
}

vector<Billet*> GestionnaireMembres::trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const
{
	auto billet = membre->getBillets();
	vector<Billet*> billetTrouver;
	copy_if(billet.begin(), billet.end(), back_inserter(billetTrouver),[prixInf, prixSup](Billet* a) {return (a->getPrix() >= prixInf && a->getPrix() <= prixSup); });
	return billetTrouver;
}

void GestionnaireMembres::afficher(ostream& o) const
{
	//TODO
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for (auto iter : conteneur_)
	{
		iter.second->afficher(o);
	}
}
