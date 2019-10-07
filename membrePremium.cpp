#include "membrePremium.h"





/****************************************************************************
 * Methode: MembrePremium
 * Description: Constructeur par param�tres
 * Param�tres: nom (string) 
 * Type de retour: aucun
 ****************************************************************************/
MembrePremium::MembrePremium(const string & nom): MembreRegulier(nom,Membre_Premium) , joursRestants_(JOUR_RESTANT_INITIALE) , pointsCumules_(0
)
{
}


/****************************************************************************
 * Methode: setJourRestants
 * Description: modifier la valeur de joursRestants_
 * Param�tres: joursRestants (unsigned int )
 * Type de retour: aucun
 ****************************************************************************/
void MembrePremium::setJourRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;
}



/****************************************************************************
 * Methode: modifierPointsCumules
 * Description: modifier la valeur de pointsCumules_
 * Param�tres: points (unsigned int)
 * Type de retour: aucun
 ****************************************************************************/
void MembrePremium::modifierPointsCumules(unsigned int pointCumulee)
{
	pointsCumules_ += pointCumulee;
}



/****************************************************************************
 * Methode: getJourRestants
 * Description: r�cup�re joursRestants_
 * Param�tres: aucun
 * Type de retour: unsigned int
 ****************************************************************************/
unsigned int MembrePremium::getJourRestants() const
{
	return joursRestants_;
}




/****************************************************************************
 * Methode: getpointsCumulee
 * Description: r�cup�re pointsCumules_
 * Param�tres: aucun
 * Type de retour: unsigned int
 ****************************************************************************/
unsigned int MembrePremium::getpointsCumulee() const
{
	return pointsCumules_;
}




/*******************************************************************************************
 * Methode: ajouterBillet
 * Description: Construit un billet, et l'ajoute � un membre
 * Param�tres: - const string& : pnr , od , dateVol .
 *			   - double : prix
 *			   - TarifBillet : tarif
 *			   - TypeBillet : typeBillet
 * Type de retour: aucun
 ********************************************************************************************/
void MembrePremium::ajouterBillet(const string & pnr, double prix, const string & od, TarifBillet tarif, TypeBillet typeBillet, const string & dateVol)
{
	MembreRegulier::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	for (unsigned int i = 0; i < billets_.size(); i++)
		if (billets_[i]->getPnr() == pnr)
			modifierPointsCumules(calculerPoints(billets_[i]));
}
	



/**************************************************************************************************************************
 * Methode: acheterCoupon
 * Description: Permet d'ajouter un coupon � un membre s'il a assez de points pour l'acheter et lui appliquer un rabais 
 *				sur le cout du coupon s'il a assez de points cumul�es pour l'avoir.
 * Param�tres: - Coupon*  : coupon
 * Type de retour: aucun
 **************************************************************************************************************************/
void MembrePremium::acheterCoupon(Coupon * coupon)
{
	double rabais = 0, nouvelCout = 0;;
	if (pointsCumules_ <= 20000){
		rabais = 0.01*pointsCumules_ / 1000;
		nouvelCout = coupon->getCout() - coupon->getCout()*rabais;
			if (points_ >= nouvelCout) {
				coupon->setCout(nouvelCout);
				MembreRegulier::acheterCoupon(coupon);
			}
	}
}


/*******************************************************************************************
 * Methode: operator<<
 * Description: permet d'afficher les informations d'un membrePremium
 * Param�tres: ostream& : os
 *			   const MembrePremium& : membrePremium
 * Type de retour: ostream
 ********************************************************************************************/
ostream & operator<<(ostream & os, const MembrePremium & membrePremium)
{
	MembreRegulier m(membrePremium);
	os << m << endl;
	os << "\t" << "- Points Cumulee :" << membrePremium.getpointsCumulee() << endl;
	os << "\t" << "- Jours Premium Restants :" << membrePremium.getJourRestants() << endl;
	return os;
}
