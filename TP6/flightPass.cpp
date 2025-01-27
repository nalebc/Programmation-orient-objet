/********************************************
* Titre: Travail pratique #6 - flightPass.cpp
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/
#include "flightPass.h"

FlightPass::FlightPass(const string& pnr, double prix, const string& od, TarifBillet tarif) : 
	Billet(pnr, prix, od, tarif), nbUtilisationsRestante_(NB_UTILISATIONS_INITIALE)
{
}

int FlightPass::getNbUtilisationsRestante() const
{
	return nbUtilisationsRestante_;
}

void FlightPass::decrementeNbUtilisations()
{
	--nbUtilisationsRestante_;
}

FlightPass* FlightPass::clone() const
{
	return new FlightPass(*this);
}

void FlightPass::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Utilisation restantes" << ": " << nbUtilisationsRestante_ << endl;
}
