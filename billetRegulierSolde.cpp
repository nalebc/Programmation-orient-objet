/*
* Titre : billetRegulierSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "billetRegulierSolde.h"

// TODO
BilletRegulierSolde::BilletRegulierSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol, double pourcentageSolde):
	BilletRegulier(pnr,prix,od,tarif,dateVol), Solde(pourcentageSolde)
{
}

// TODO
double BilletRegulierSolde::getPrix() const
{
	return (prix_ - prix_*pourcentageSolde_);

}

// TODO
double BilletRegulierSolde::getPrixBase()
{
	return prix_;
}

// TODO
BilletRegulierSolde* BilletRegulierSolde::clone()
{
	return (new BilletRegulierSolde(*this));
}

// TODO
void BilletRegulierSolde::afficher(ostream& o)
{
	BilletRegulier::afficher(o);
	o << "\t\t\t" << setw(11) << "- Pourcentage solde " << ": " << pourcentageSolde_ << "%" << endl;
}