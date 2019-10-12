/*
* Titre : solde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe C�T�-MORNEAULT
*/

#include "solde.h"

Solde::Solde(double pourcentageSolde)
{
	pourcentageSolde_ = pourcentageSolde;
}

Solde::~Solde()
{
}

double Solde::getPourcentageSolde() const
{
	return pourcentageSolde_;
}

void Solde::setPourcentageSolde(double pourcentageSolde)
{
	pourcentageSolde_ = pourcentageSolde;
}
