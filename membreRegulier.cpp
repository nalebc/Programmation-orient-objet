#include "membreRegulier.h"




/****************************************************************************
 * Methode: MembreRegulier
 * Description: Constructeur par paramètres
 * Paramètres: nom (string) , typeMembre(TypeMembre)
 * Type de retour: aucun
 ****************************************************************************/
MembreRegulier::MembreRegulier(const string & nom, TypeMembre typeMembre) : Membre(nom, typeMembre), points_(0){}





/****************************************************************************
 * Methode: getPoints
 * Description: récupère points_
 * Paramètres: aucun
 * Type de retour: int
 ****************************************************************************/
int MembreRegulier::getPoints() const
{
	return points_;
}



/****************************************************************************
 * Methode: getCoupons
 * Description: récupère coupons_
 * Paramètres: aucun
 * Type de retour: vector<Coupon*>
 ****************************************************************************/
vector<Coupon*> MembreRegulier::getCoupons() const
{
	return coupons_;
}




/**************************************************************************************************************************
 * Methode: acheterCoupon
 * Description: Permet d'ajouter un coupon à un membre s'il a assez de points pour l'acheter
 * Paramètres: - Coupon*  : coupon
 * Type de retour: aucun
 **************************************************************************************************************************/
void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	if (points_ > coupon->getCout()) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}





/*******************************************************************************************
 * Methode: operator+=
 * Description: permet d'additionner un coupon à un membre directement
 * Paramètres: Coupon* : coupon
 * Type de retour: Membre
 ********************************************************************************************/
Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}




/*******************************************************************************************
 * Methode: operator-=
 * Description: permet de soustraire un coupon à un membre directement
 * Paramètres: Coupon* : coupon
 * Type de retour: Membre
 ********************************************************************************************/
Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	for (unsigned int i = 0; i < coupons_.size(); i++) {
		if (coupons_[i] == coupon) {
			coupons_[i] = coupons_[coupons_.size() - 1];
			coupons_.pop_back();
			return *this;
		}
	}

	return *this;
}

/****************************************************************************
 * Methode: modifierPoints
 * Description: modifier la valeur de points_
 * Paramètres: points (int)
 * Type de retour: aucun
 ****************************************************************************/
void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}



/*******************************************************************************************
 * Methode: ajouterBillet
 * Description: Construit un billet, et l'ajoute à un membre
 * Paramètres: - const string& : pnr , od , dateVol .
 *			   - double : prix
 *			   - TarifBillet : tarif
 *			   - TypeBillet : typeBillet
 * Type de retour: aucun
 ********************************************************************************************/
void MembreRegulier::ajouterBillet(const string & pnr, double prix, const string & od, TarifBillet tarif, TypeBillet typeBillet, const string & dateVol)
{
	Membre::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	for (unsigned int i = 0; i < billets_.size(); i++)
		if (billets_[i]->getPnr() == pnr)
			modifierPoints(calculerPoints(billets_[i]));

}




/***********************************************************************************
* Methode: calculerPoints
* Description : calcule le nombre de points que rapporte un billet dépendamment du tarif du
*				billet.
* Paramètres : Billet * : billet
* Type de retour : double
********************************************************************************************/
double MembreRegulier::calculerPoints(Billet* billet) const
{
	double bonus = 0;
	switch (billet->getTarif()) {
	case TarifBillet::PremiumEconomie:
		bonus = 50;
		break;
	case TarifBillet::Affaire:
		bonus = 150;
		break;
	case TarifBillet::Premiere:
		bonus = 300;
		break;
	default:
		break;
	}

	return billet->getPrix() * 0.10 + bonus;
}





/*******************************************************************************************
 * Methode: operator<<
 * Description: permet d'afficher les informations d'un membreRegulier
 * Paramètres: ostream& : os
 *			   const MembreRegulier& : membreRegulier
 * Type de retour: ostream
 ********************************************************************************************/
ostream & operator<<(ostream & os, const MembreRegulier & membreRegulier)
{

	Membre m(membreRegulier);
	os << m; 
	os << "\t" <<"- Points : " << membreRegulier.getPoints() << endl;
	os << "\t" <<"- Coupons : " << endl ;
	for (unsigned int i = 0; i < membreRegulier.getCoupons().size(); i++)
		os << membreRegulier.getCoupons()[i];
	cout << endl;
	return os;
}
