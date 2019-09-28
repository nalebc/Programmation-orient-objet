#include "membrePremium.h"

MembrePremium::MembrePremium(const string & nom): MembreRegulier(nom,Membre_Premium) , joursRestants_(JOUR_RESTANT_INITIALE) , pointsCumules_(0)
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
	if (pointsCumules_ >=1000 )
		if(coupon->getRabais() <=20)
		coupon->setRabais(coupon->getRabais() + 0.01);
	MembreRegulier::acheterCoupon(coupon);
}

ostream & operator<<(ostream & os, const MembrePremium & membrePremium)
{
	MembreRegulier m(membrePremium);
	os << m << endl;
	os << membrePremium.getpointsCumulee() << endl;
	os << membrePremium.getJourRestants() << endl;
	return os;
}
