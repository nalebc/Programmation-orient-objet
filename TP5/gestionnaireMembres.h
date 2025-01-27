#pragma once
/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef GESTIONNAIREMEMBRES_H
#define	GESTIONNAIREMEMBRES_H

#include <vector>

#include "membrePremium.h"
#include "solde.h"
#include "gestionnaireGenerique.h"
#include "foncteur.h"

class GestionnaireMembres: public GestionnaireGenerique< map<string, Membre*> ,pair<string, Membre*>, AjouterMembre> {
public:

	void assignerBillet(Billet* billet, const string& nomMembre, int rabaisCoupon);

	//TODO
	double calculerRevenu() const;

	//TODO
	int calculerNombreBilletsEnSolde() const;

	//TODO
	Billet* getBilletMin(string nomMembre) const ;

	//TODO
	Billet* getBilletMax(string nomMembre) const ;

	//TODO
	vector<Billet*>trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const;

	//TODO
	void afficher(ostream& o) const;
};
#endif // !GESTIONNAIREMEMBRES_H



