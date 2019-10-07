#include "billetRegulier.h"




/****************************************************************************
 * Methode: BilletRegulier
 * Description: Constructeur par param�tres
 * Param�tres:  string : pnr, string : nomPassager, double : prix,string : od, 
 *              TarifBillet : tarif,  string : dateVol,TypeBillet typeBillet
 * Type de retour: aucun
 ****************************************************************************/
BilletRegulier::BilletRegulier(const string & pnr, const string & nomPassager, double prix, const string & od, TarifBillet tarif, const string & dateVol,
	TypeBillet typeBillet) : Billet(pnr, nomPassager, prix, od, tarif, typeBillet), dateVol_(dateVol)
{

}



/****************************************************************************
 * Methode: getDateVol
 * Description: r�cup�re dateVol_
 * Param�tres: aucun
 * Type de retour: string
 ****************************************************************************/
string BilletRegulier::getDateVol() const
{
	return dateVol_;
}




/****************************************************************************
 * Methode: setDateVol
 * Description: r�cup�re dateVol_
 * Param�tres: string : dateVol
 * Type de retour: aucun
 ****************************************************************************/
void BilletRegulier::setDateVol(string dateVol)
{
	dateVol_ = dateVol;
}


/****************************************************************************
* Surcharge de l'operateur <<
* Description: Affiche un BilletRegulier
* Param�tres:	- ostream : os
*				- BilletRegulier : billet
* Type de retour: ostream
****************************************************************************/
ostream & operator<<(ostream & o, const BilletRegulier & billet)
{
	Billet b(billet);
	o << b;
	o << "\t\t\t" << setw(11) <<"- Date  " << ": " << billet.getDateVol() << endl;
	return o;
}
