#include "membre.h"

Membre::Membre()
{	
	nom_ = "default";
	points_ = 0; 
	nbBillets_ = 0;
	nbCoupons_ = 0;
	capaciteBillets_ = CAPACITE_INITIALE;
	capaciteCoupons_ = CAPACITE_INITIALE;
	billets_ = new Billet * [CAPACITE_INITIALE];
	coupons_ = new Coupon * [CAPACITE_INITIALE];
}

Membre::Membre(const string& nom_):nom_(nom_)
{
	points_ = 0;
	nbBillets_ = 0;
	nbCoupons_ = 0;
	capaciteBillets_ = CAPACITE_INITIALE;
	capaciteCoupons_ = CAPACITE_INITIALE;
	billets_ = new Billet * [CAPACITE_INITIALE];
	coupons_ = new Coupon * [CAPACITE_INITIALE];
}

Membre::~Membre()
{
	for (int i = 0; i < nbBillets_; i++)
	{
		delete billets_[i];
	}
	delete[] billets_;
	delete[] coupons_;
}

string Membre::getNom()
{
	return nom_;
}
int Membre::getPoints()
{
	return points_;
}

Billet** Membre::getBillets()
{
	return billets_;
}

int Membre::getNbBillets()
{
	return nbBillets_;
}
int Membre::getCapaciteBillets()
{
	return capaciteBillets_;
}

Coupon** Membre::getCoupons()
{
	return coupons_;
}

int Membre::getNbCoupons()
{
	return nbCoupons_;
}
int Membre::getCapaciteCoupons()
{
	return capaciteCoupons_;
}
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

void Membre::modifierPoints(int points)
{
	points_+= points;
}

void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	Billet* billets = new Billet(pnr, nom_, prix, od, tarif, dateVol);
	if (capaciteBillets_<=nbBillets_)
	{
		if (capaciteBillets_ > 0)
			capaciteBillets_ *= 2;
		else
			capaciteBillets_ = 10;
		Billet** copy = new Billet*[capaciteBillets_];
		for (int i = 0; i < nbBillets_; i++)
		{
			copy[i] = billets_[i];
		}
		delete[] billets_;
		billets_ = copy;
	}
	billets_[nbBillets_++] = billets;
	modifierPoints(calculerPoints(billets));
}

void Membre::ajouterCoupon(Coupon* coupon)
{
	if (capaciteCoupons_ <= nbCoupons_)
	{
		if (capaciteCoupons_ > 0)
			capaciteCoupons_ *= 2;
		else
			capaciteCoupons_ = 10;
		Coupon** copy = new Coupon * [capaciteCoupons_];
		for (int i = 0; i < nbCoupons_; i++)
		{
			copy[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = copy;
	}
	coupons_[nbCoupons_++] = coupon;
}

void Membre::retirerCoupon(Coupon* coupon)
{
	for (int i = 0; i < nbCoupons_; i++)
	{
		if (coupons_[i] == coupon)
		{
			coupons_[i] = coupons_[nbCoupons_-1];
			coupons_[nbCoupons_-1] = nullptr;
			nbCoupons_--;
			return;
		}
	}
}

void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_>=coupon->getCout())
	{
		ajouterCoupon(coupon);
		modifierPoints(-coupon->getCout());
	}
}
double Membre::calculerPoints(Billet* billet)
{
	switch (billet->getTarif())
	{
		case(TarifBillet::PremiumEconomie):return billet->getPrix() * 0.1 + 50;
			break;
		case(TarifBillet::Affaire):return billet->getPrix() * 0.1 + 150;
			break;
		case(TarifBillet::Premiere):return billet->getPrix() * 0.1 + 300;
			break;
		default:return billet->getPrix() * 0.1;
			break;
	}
}

void Membre::afficherMembre()
{
	cout << "test membre" << endl;
}