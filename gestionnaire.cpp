/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "gestionnaire.h"





 /****************************************************************************
  * Methode: Gestionnaire
  * Description: Constructeur par défaut
  * Paramètres: aucun
  * Type de retour: aucun
  ****************************************************************************/
Gestionnaire::Gestionnaire()
{
}






/****************************************************************************
 * Methode: Gestionnaire
 * Description: Distructeur
 * Paramètres: aucun
 * Type de retour: aucun
 ****************************************************************************/
Gestionnaire::~Gestionnaire()
{
	for (int i = 0; i < membres_.size(); i++) {
		delete membres_[i];
	}

	for (int i = 0; i < coupons_.size(); i++) {
		delete coupons_[i];
	}
}



/****************************************************************************
 * Methode: getMembres
 * Description: récupère membres_
 * Paramètres: aucun
 * Type de retour: vector<Membre*>
 ****************************************************************************/
vector<Membre*> Gestionnaire::getMembres() const
{
	return membres_;
}


/****************************************************************************
 * Methode: getCoupons
 * Description: récupère coupons_
 * Paramètres: aucun
 * Type de retour: vector<Coupon*>
 ****************************************************************************/
vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}





/*******************************************************************************************
 * Methode: ajouterMembre
 * Description: crée un membre à partir du constructeur, et l'ajoute
 * Paramètres: - const string& : nomMembre
 * Type de retour: aucun
 ********************************************************************************************/
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






/*******************************************************************************************
 * Methode: ajouterCoupon
 * Description: crée un coupon à partir du constructeur, et l'ajoute 
 * Paramètres: - const string& : code ,   double : rabais, int : cout
 * Type de retour: aucun
 ********************************************************************************************/
void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	coupons_.push_back(new Coupon(code, rabais, cout));
}




/*******************************************************************************************
 * Methode: trouverMembre
 * Description: trouve le membre tel que son nom_=nomMmembre
 * Paramètres: - const string& : nom Membre
 * Type de retour: Membre*
 ********************************************************************************************/
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




/*******************************************************************************************
 * Methode: assignerBillet
 * Description: assigne un billet a un membre en appliquant un coupon ou non
 * Paramètres: - const string& : nomMembre , pnr , od , dateVol .
 *			   - double : prixBase
 *			   - TarifBillet : tarif
 *			   - TypeBillet : typeBillet
 * Type de retour: aucun
 ********************************************************************************************/
void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol,
	bool utiliserCoupon, TypeBillet typeBillet)
{
	if (trouverMembre(nomMembre) == nullptr)return;
	Membre* membre = trouverMembre(nomMembre);
	MembrePremium* membrePremium = static_cast<MembrePremium*>(trouverMembre(nomMembre));
	double prixReel, rabais ;
	if (typeBillet == Flight_Pass)
		prixBase *= 10;
	if (membre->getTypeMembre() == Membre_Premium) {
		if (membrePremium->getpointsCumulee() <= 20000) {
			rabais = (int)(membrePremium->getpointsCumulee() / 1000)*0.005;
			prixBase -= (rabais*prixBase);
		}
	}
		if (utiliserCoupon) 
		 prixReel = prixBase - appliquerCoupon(membrePremium, prixBase); 
		else 
			prixReel = prixBase;
		
		membrePremium->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
	
}





/*******************************************************************************************
 * Methode: appliquerCoupon
 * Description: applique le meilleur coupon (celui  qui a le rabais maximum) a un prix
 * Paramètres: - double : prix
 *			   - Membre* : membre
 * Type de retour: double
 ********************************************************************************************/
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	 MembrePremium* membrePremium = static_cast<MembrePremium*>(membre);
	if (   membrePremium->getCoupons().size() ==0  ){
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}
	 Coupon* meilleurCoupon = membrePremium->getCoupons()[0];
		for (int i = 1; i < membrePremium->getCoupons().size(); ++i) {
			if (*membrePremium->getCoupons()[i] > *meilleurCoupon) {
				meilleurCoupon = membrePremium->getCoupons()[i];
			}
		} 
		*membrePremium -= meilleurCoupon; 


	return prix * meilleurCoupon->getRabais();
}





/**************************************************************************************************************************
 * Methode: acheterCoupon
 * Description: Trouve d'abord le coupons avec le plus gros rabais tout en verifiant que le membre a les points qu'il faut,
 *				ensuite si le membre a les points en lui ajoute le coupons sinon en affiche message d'erreur
 * Paramètres: - const string& : nomMmembre
 * Type de retour: aucun
 **************************************************************************************************************************/
void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	if (coupons_.size() == 0) {
		cout << "Le gestionnaire n'a pas de coupon!" << endl;
		return;
	}
		MembreRegulier* membreCaste = static_cast<MembreRegulier*>(trouverMembre(nomMembre));
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



/*******************************************************************************************
 * Methode: operator<<
 * Description: afficher tous les membre d'un gestionnaire avec leur infos
 * Paramètres: ostream& os, const Gestionnaire& gest
 * Type de retour: ostream
 ********************************************************************************************/
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
