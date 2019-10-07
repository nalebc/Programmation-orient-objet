#include "flightPass.h"







/****************************************************************************
 * Methode: FlightPass
 * Description: Constructeur par paramètres
 * Paramètres: string : pnr , string : nomPassager , double : prix , string : od 
 *             TarifBillet : tarif , TypeBillet : typeBillet 
 * Type de retour: aucun
 ****************************************************************************/
FlightPass::FlightPass(const string & pnr, const string & nomPassager, double prix, const string & od, TarifBillet tarif, TypeBillet typeBillet):
	Billet(pnr,nomPassager,prix,od,tarif,typeBillet), nbUtilisationsRestante_(NB_UTILISATIONS_INITIALE)

{

}



/****************************************************************************
 * Methode: decrementeNbUtilisations
 * Description: décremente nbUtilisationsRestante_
 * Paramètres: aucun
 * Type de retour: aucun
 ****************************************************************************/
void FlightPass::decrementeNbUtilisations()
{
	nbUtilisationsRestante_--;
}


/****************************************************************************
 * Methode: getNbUtilisationsRestante
 * Description: récupère nbUtilisationsRestante_
 * Paramètres: aucun
 * Type de retour: int
 ****************************************************************************/
int FlightPass::getNbUtilisationsRestante() const
{
	return nbUtilisationsRestante_;
}



/****************************************************************************
* Surcharge de l'operateur <<
* Description: Affiche un Billet Flightpass
* Paramètres:	- ostream : os
*				- FlightPass : flightpass
* Type de retour: ostream
****************************************************************************/
ostream & operator<<(ostream & os, const FlightPass & flightpass)
{
	Billet b(flightpass);
	os << b;
	os << "\t\t\t" << setw(11) << "- Utilisations restantes  " << ": " << flightpass.getNbUtilisationsRestante() << endl;
	return os;
}
