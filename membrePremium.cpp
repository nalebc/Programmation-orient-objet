#include "membrePremium.h"





MembrePremium::MembrePremium(const string & nom): MembreRegulier(nom,Membre_Premium) , joursRestants_(JOUR_RESTANT_INITIALE) , pointsCumules_(0
)
{
}

void MembrePremium::setJourRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;
}

void MembrePremium::modifierPointsCumules(unsigned int pointCumulee)
{
	pointsCumules_ += pointCumulee;
}

unsigned int MembrePremium::getJourRestants() const
{
	return joursRestants_;
}

unsigned int MembrePremium::getpointsCumulee() const
{
	return pointsCumules_;
}

void MembrePremium::ajouterBillet(const string & pnr, double prix, const string & od, TarifBillet tarif, TypeBillet typeBillet, const string & dateVol)
{
	MembreRegulier::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	for (unsigned int i = 0; i < billets_.size(); i++)
		if (billets_[i]->getPnr() == pnr)
			modifierPointsCumules(calculerPoints(billets_[i]));
}
	
void MembrePremium::acheterCoupon(Coupon * coupon)
{
	double rabais = 0, nouvelCout = 0;;
	if (pointsCumules_ <= 20000){
		//rabais = (int)(pointsCumules_ / 1000)*0.01*coupon->getCout();
		rabais = 0.01*pointsCumules_ / 1000;
		nouvelCout = coupon->getCout() - coupon->getCout()*rabais;
			if (points_ >= nouvelCout) {
				coupon->setCout(nouvelCout);
				MembreRegulier::acheterCoupon(coupon);
			}
	}
}

ostream & operator<<(ostream & os, const MembrePremium & membrePremium)
{
	MembreRegulier m(membrePremium);
	os << m << endl;
	os << "\t" << "- Points Cumulee :" << membrePremium.getpointsCumulee() << endl;
	os << "\t" << "- Jours Premium Restants :" << membrePremium.getJourRestants() << endl;
	return os;
}
