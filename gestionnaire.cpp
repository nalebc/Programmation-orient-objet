/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "gestionnaire.h"

Gestionnaire::Gestionnaire()
{
}

Gestionnaire::~Gestionnaire()
{
	for (int i = 0; i < membres_.size(); i++) {
		delete membres_[i];
	}

	for (int i = 0; i < coupons_.size(); i++) {
		delete coupons_[i];
	}
}

vector<Membre*> Gestionnaire::getMembres() const
{
	return membres_;
}

vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}

void Gestionnaire::ajouterMembre(const string& nomMembre, TypeMembre typeMembre)
{
	switch (typeMembre) {
	case Membre_Premium: 
		membres_.push_back(new MembrePremium(nomMembre)); break;
	case Membre_Regulier:
		membres_.push_back(new MembreRegulier(nomMembre,typeMembre)); break;
	case Membre_Occasionnel:
		membres_.push_back(new Membre(nomMembre,typeMembre)); break;
	}
}

void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	coupons_.push_back(new Coupon(code, rabais, cout));
}

Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (int i = 0; i < membres_.size(); i++) {
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}

void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol,
	bool utiliserCoupon, TypeBillet typeBillet)
{
	if (trouverMembre(nomMembre) == nullptr)return;
	Membre* membre = trouverMembre(nomMembre);
	MembrePremium* membrePremium = static_cast<MembrePremium*>(trouverMembre(nomMembre));
	double prixReel, rabais , prixtempo = prixBase;
	if (typeBillet == Flight_Pass)
		prixBase *= 10;
	if (membre->getTypeMembre() == Membre_Premium) {
		if (membrePremium->getpointsCumulee() <= 20000) {
			rabais = (int)(membrePremium->getpointsCumulee() / 1000)*0.005;
			prixBase -= (rabais*prixBase);
			membrePremium->modifierPointsCumules((rabais/0.005)*1000);
		}
	}
		if (utiliserCoupon) 
		 prixReel = prixBase - appliquerCoupon(membrePremium, prixBase); 
		else 
			prixReel = prixBase;
		
		membre->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
	
}


double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	 MembrePremium* membrePremium = static_cast<MembrePremium*>(membre);
	if (   membrePremium->getCoupons().size() ==0  ){
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}
	Coupon* meilleurCoupon;
		meilleurCoupon = membrePremium->getCoupons()[0];
		for (int i = 1; i < membrePremium->getCoupons().size(); ++i) {
			if (*membrePremium->getCoupons()[i] > *meilleurCoupon) {
				meilleurCoupon = membrePremium->getCoupons()[i];
			}
		} 
		*membrePremium -= meilleurCoupon; 


	return prix * meilleurCoupon->getRabais();
}

void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	if (coupons_.size() == 0) {
		cout << "Le gestionnaire n'a pas de coupon!" << endl;
		return;
	}
		MembrePremium* membreCaste = static_cast<MembrePremium*>(trouverMembre(nomMembre));
		if (membreCaste == nullptr) {
			return;
		}
		Coupon* meilleurCoupon = nullptr;
		for (int i = 0; i < coupons_.size(); i++) {
			if (membreCaste->getPoints() >= coupons_[i]->getCout()) {
				// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
				if (meilleurCoupon == nullptr) {
					meilleurCoupon = coupons_[i];
				}
				// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
				else if (*coupons_[i] > *meilleurCoupon) {
					meilleurCoupon = coupons_[i];
				}
			}
		}
		if (trouverMembre(nomMembre)->getTypeMembre() == Membre_Regulier)
		{
			MembreRegulier* membreRegulier = static_cast<MembreRegulier*>(trouverMembre(nomMembre));
			if (meilleurCoupon) {
				membreRegulier->acheterCoupon(meilleurCoupon);
			}
			else 
				cout << "Le membre ne peut acheter de coupon\n";
		}
		else {
			MembrePremium* membrePremium = static_cast<MembrePremium*>(trouverMembre(nomMembre));
			if (meilleurCoupon) {
				membrePremium->acheterCoupon(meilleurCoupon);
			}
			else
				cout << "Le membre ne peut acheter de coupon\n";
		}
	}


ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	
	for (int i = 0; i < gestionnaire.membres_.size(); i++) {
		if (gestionnaire.membres_[i]->getTypeMembre() == Membre_Regulier) {
			MembreRegulier* membreRegulier = static_cast<MembreRegulier*>(gestionnaire.membres_[i]);
			o << *membreRegulier;
		}
		else if (gestionnaire.membres_[i]->getTypeMembre() == Membre_Premium) {
			MembrePremium* membrePremium = static_cast<MembrePremium*>(gestionnaire.membres_[i]);
			o << *membrePremium;
		}
		else 
				o << *gestionnaire.membres_[i]; 
		
	}

	return o;
}
