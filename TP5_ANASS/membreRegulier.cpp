/********************************************
* Titre: Travail pratique #5 - membreRegulier.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "membreRegulier.h"
#include <algorithm>

MembreRegulier::MembreRegulier(const string& nom) : 
	Membre(nom), points_(0)
{
}

int MembreRegulier::getPoints() const
{
	return points_;
}

vector<Coupon*> MembreRegulier::getCoupons() const
{
	return coupons_;
}

void MembreRegulier::ajouterBillet(Billet* billet)
{
	Membre::ajouterBillet(billet);
	modifierPoints(calculerPoints(billets_.back()));
}

Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

//todo
Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	//coupons_.erase((find(begin(coupons_), end(coupons_), [coupon](Coupon* c) {return coupon == c; })));	
	//coupons_.erase(find_if(coupons_.begin(), coupons_.end(), [coupon](Coupon* c) { return coupon == c; }));
	coupons_.erase(find(begin(coupons_), end(coupons_), coupon));
	//remove si on veut supprimer tout les coupon dupliquer
	return *this;
}

void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}

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

bool MembreRegulier::peutAcheterCoupon(Coupon* coupon) const
{
	return points_ >= coupon->getCout();
}

void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	if (peutAcheterCoupon(coupon)) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}


//todo
void MembreRegulier::afficher(ostream& o) const
{
	Membre::afficher(o);
	copy(begin(coupons_), end(coupons_), ostream_iterator<Coupon*>(o, " "));
}
