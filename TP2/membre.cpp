/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

Membre::Membre() :
	nom_(""),
	points_(0)
{
}

Membre::Membre(const string& nom) :
	nom_(nom),
	points_(0)
{
}
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_),
	points_(membre.points_)
{
	coupons_ = membre.coupons_;
	for (int i = 0; i < membre.billets_.size(); i++)
	{
		billets_.push_back(new Billet(membre.billets_[i]->getPnr(), membre.billets_[i]->getNomPassager(), membre.billets_[i]->getPrix(), membre.billets_[i]->getOd(), membre.billets_[i]->getTarif(), membre.billets_[i]->getDateVol()));
	}

}

Membre::~Membre()
{
	for (int i = 0; i < billets_.size(); ++i)
	{
		delete billets_[i];
	}
}

string Membre::getNom() const
{
	return nom_;
}

int Membre::getPoints() const
{
	return points_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

vector<Coupon*> Membre::getCoupons() const
{
	return coupons_;
}


void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

void Membre::modifierPoints(int points)
{
	points_ += points;
}

void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, dateVol);
	billets_.push_back(billet);
	modifierPoints(calculerPoints(billet));
}

void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_ > coupon->getCout()) {
		// TODO: Utiliser la surcharge de l'operateur += de la classe Membre plutot qu'utiliser la methode ajouterCoupon
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}

double  Membre::calculerPoints(Billet * billet) const
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

	return billet->getPrix()* 0.10 + bonus;
}

// TODO: Remplacer cette methode par l'operateur +=
Membre& Membre::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);
	return *this;
}

// TODO: Remplacer cette methode par l'operateur -=
Membre& Membre::operator-=(Coupon* coupon)
{
	for (int i = 0; i < coupons_.size(); ++i)
	{
		if (coupons_[i] == coupon)
		{
			coupons_[i] = coupons_[coupons_.size() - 1];
		}
	}
	coupons_.pop_back();
	return *this;
}

bool Membre::operator==(const string& nom) const
{
	return(nom_ == nom);
}
bool operator==(const string& nom, Membre& membre)
{
	return (membre==nom);
}

Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre)
	{
		nom_ = membre.nom_;
		points_ = membre.points_;
		coupons_ = membre.coupons_;
		for (int i = 0; i < billets_.size(); ++i)
		{
			delete billets_[i];
		}
		billets_.clear();
		for (int i = 0; i < membre.billets_.size(); i++)
		{
			billets_.push_back(new Billet(membre.billets_[i]->getPnr(), membre.billets_[i]->getNomPassager(), membre.billets_[i]->getPrix(), membre.billets_[i]->getOd(), membre.billets_[i]->getTarif(), membre.billets_[i]->getDateVol()));
		}

	}
	return *this;
}


ostream& operator<<(ostream& out, const Membre& membre)
{
	// TODO: insert return statement here
	out << setfill(' ');
	out << "- Membre " << membre.nom_ << ":" << endl;
	out << "\t" << left << setw(10) << "- Points" << ": " << membre.points_ << endl;
	out << "\t" << "- Billets :" << endl;
	for (int i = 0; i < membre.billets_.size(); i++) {
		out << *membre.billets_[i];
	}
	out << "\t" << "- Coupons :" << endl;
	for (int i = 0; i < membre.coupons_.size(); i++) {
		out << *membre.coupons_[i];
	}
	out << endl;
	return out;
}
