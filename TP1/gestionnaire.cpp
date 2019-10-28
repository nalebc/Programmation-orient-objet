#include "gestionnaire.h"

Gestionnaire::Gestionnaire()
{
	membres_ = new Membre * [CAPACITE_INITIALE];
	nbMembres_ = 0;
	capaciteMembres_ = CAPACITE_INITIALE;
	coupons_ = new Coupon * [CAPACITE_INITIALE];
	nbCoupons_ = 0;
	capaciteCoupons_ = CAPACITE_INITIALE;
}

Gestionnaire::~Gestionnaire()
{
	for (int i = 0; i < nbMembres_; i++)
	{
		delete membres_[i];
	}
	delete[] membres_;
	for (int i = 0; i < nbCoupons_; i++) {
		delete coupons_[i];
	}
	delete[] coupons_;
}

Membre** Gestionnaire::getMembres()
{
	return membres_;
}
int Gestionnaire::getNbMembres()
{
	return nbMembres_;
}
int Gestionnaire::getCapaciteMembres()
{
	return capaciteMembres_;
}
Coupon** Gestionnaire::getCoupons()
{
	return coupons_;
}
int Gestionnaire::getNbCoupons()
{
	return nbCoupons_;
}
int Gestionnaire::getCapaciteCoupons()
{
	return capaciteCoupons_;
}
void Gestionnaire::ajouterMembre(const string& nomMembre)
{
	Membre* membres = new Membre(nomMembre);
	if (nbMembres_ >= capaciteMembres_)
	{
		if (capaciteMembres_ > 0)
			capaciteMembres_ *= 2;
		else
			capaciteMembres_ = 10;
		Membre** copy = new Membre * [capaciteMembres_];
		for (int i = 0; i < nbMembres_; i++)
		{
			copy[i] = membres_[i];
		}
		delete[] membres_;
		membres_ = copy;
	}
	membres_[nbMembres_++]=membres;
}
void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	Coupon* coupons = new Coupon(code, rabais, cout);
	if (nbCoupons_ >= capaciteCoupons_)
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
	coupons_[nbCoupons_++] = coupons;
}

Membre* Gestionnaire::trouverMembre(const string& nomMembre)
{
	Membre* retour = nullptr;
	for (int i = 0; i < nbMembres_; i++)
	{
		if (membres_[i]->getNom() == nomMembre)
		{
			retour=this->membres_[i];
		}
	}
	return retour;
}

void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon)
{
	double newPrixBase;
	if (utiliserCoupon)
	{
		newPrixBase=appliquerCoupon(trouverMembre(nomMembre), prixBase);
		trouverMembre(nomMembre)->ajouterBillet(pnr, newPrixBase, od, tarif, dateVol);
	}
	else
		trouverMembre(nomMembre)->ajouterBillet(pnr, prixBase, od, tarif, dateVol);
}

double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	double max = 0;
	int pos = 0;
	for (int i = 0; i < membre->getNbCoupons(); i++)
	{
		if (max < membre->getCoupons()[i]->getRabais())
		{
			max = membre->getCoupons()[i]->getRabais();
			pos = i;
		}
	}
	membre->retirerCoupon(membre->getCoupons()[pos]);
	return prix * (1-max);

}

void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	double max = 0;
	int position=0;
	for (int i = 0; i < nbCoupons_; i++)
	{
		if (max < coupons_[i]->getRabais() && trouverMembre(nomMembre)->getPoints()>=coupons_[i]->getCout())
		{
			max = coupons_[i]->getRabais();
			position = i;
		}
	}
	if (trouverMembre(nomMembre)->getPoints() >= coupons_[position]->getCout())
	{
		trouverMembre(nomMembre)->ajouterCoupon(coupons_[position]);
		trouverMembre(nomMembre)->modifierPoints(-coupons_[position]->getCout());
	}
}

void Gestionnaire::afficherInfos()
{
	cout << "test gestionnaire" << endl;
}

