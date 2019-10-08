/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe C�T�-MORNEAULT
 */

#include "membre.h"

//a changer



/****************************************************************************
 * Methode: Membre
 * Description: Constructeur par d�faut
 * Param�tres: aucun
 * Type de retour: aucun
 ****************************************************************************/
Membre::Membre() :
	nom_(""), typeMembre_(Membre_Regulier)
{
}

//a changer


 /****************************************************************************
  * Methode: Membre
  * Description: Constructeur par param�tres
  * Param�tres: nom (string) , typeMembre(TypeMembre)
  * Type de retour: aucun
  ****************************************************************************/
Membre::Membre(const string& nom, TypeMembre typeMembre) :
	nom_(nom), typeMembre_ (typeMembre)
{
}
//a changer


/****************************************************************************
 * Methode: Membre
 * Description: Constructeur par copie
 * Param�tres: membre (Membre)
 * Type de retour: aucun
 ****************************************************************************/
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_), typeMembre_(membre.getTypeMembre())
{
	for (int i = 0; i < membre.billets_.size(); ++i) {
		switch (membre.billets_[i]->getTypeBillet())
		{
		case Flight_Pass:
			billets_.push_back(new FlightPass(membre.billets_[i]->getPnr(), membre.billets_[i]->getNomPassager(), membre.billets_[i]->getPrix(),
			membre.billets_[i]->getOd(), membre.billets_[i]->getTarif(), membre.billets_[i]->getTypeBillet())); break;
		case Billet_Base: billets_.push_back(new Billet(*membre.billets_[i])); break;
		case Billet_Regulier: BilletRegulier *billerRegulier = static_cast<BilletRegulier*>(membre.billets_[i]);
			billets_.push_back(new BilletRegulier(billerRegulier->getPnr(), billerRegulier->getNomPassager(), billerRegulier->getPrix(),
				billerRegulier->getOd(), billerRegulier->getTarif(),billerRegulier->getDateVol(), billerRegulier->getTypeBillet())); break;
		}

	}
}





/****************************************************************************
 * Methode: ~Membre
 * Description: Desctructeur
 * Param�tres: aucun
 * Type de retour: aucun
 ****************************************************************************/
Membre::~Membre()
{
	for (int i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}


// Getter
/****************************************************************************
 * Methode: getNom
 * Description: r�cup�re nom_
 * Param�tres: aucun
 * Type de retour: string
 ****************************************************************************/
string Membre::getNom() const
{
	return nom_;
}


/****************************************************************************
 * Methode: getTypeMembre
 * Description: r�cup�re typeMembre_
 * Param�tres: aucun
 * Type de retour: TypeMembre
 ****************************************************************************/
TypeMembre Membre::getTypeMembre() const
{
	return typeMembre_;
}




/****************************************************************************
 * Methode: getBillets
 * Description: r�cup�re billets_
 * Param�tres: aucun
 * Type de retour: vector<Billet*>
 ****************************************************************************/
vector<Billet*> Membre::getBillets() const
{
	return billets_;
}




// Setter
/****************************************************************************
 * Methode: setNom
 * Description: modifier le nom_
 * Param�tres: nom ( const string&)
 * Type de retour: aucun
 ****************************************************************************/
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}



/*******************************************************************************************
 * Methode: utiliserBillet
 * Description: permet d'enlever un billet � un membre s'il a utilis�
 * Param�tres:  pnr(string)
 * Type de retour: aucun
 ********************************************************************************************/
void Membre::utiliserBillet(const string & pnr)
{
	for (unsigned int i = 0; i < billets_.size(); i++)
		if (billets_[i]->getPnr() == pnr) {
			if (billets_[i]->getTypeBillet() == Flight_Pass) {
				FlightPass* billetFlightPass = static_cast<FlightPass*>(billets_[i]);
				if (billetFlightPass->getNbUtilisationsRestante() == 1) {
					billets_[i] = billets_[billets_.size() - 1];
					billets_.pop_back();
					delete billetFlightPass;
				}
				else
					billetFlightPass->decrementeNbUtilisations();
			}
			else {
				*billets_[i] =  *billets_[billets_.size() - 1];
				delete billets_[billets_.size() - 1];
				billets_.pop_back();
			}
		}
		else
			cout << "Erreur!!!" << endl;
	
}

// a changer


/*******************************************************************************************
 * Methode: ajouterBillet
 * Description: Construit un billet d�pendamment de son type, et l'ajoute � un membre
 * Param�tres: - const string& : pnr , od , dateVol .
 *			   - double : prix
 *			   - TarifBillet : tarif
 *			   - TypeBillet : typeBillet
 * Type de retour: aucun
 ********************************************************************************************/
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	if (typeBillet == Flight_Pass) {
		billets_.push_back(new FlightPass(pnr, nom_, prix, od, tarif, typeBillet));
	}
	 else if(typeBillet == Billet_Base) {
		billets_.push_back(new Billet(pnr, nom_, prix, od, tarif, typeBillet));
	}
	 else if (typeBillet == Billet_Regulier) {
		billets_.push_back(new BilletRegulier(pnr, nom_, prix, od, tarif,dateVol, typeBillet));
	}



	//inutile, cette classe ne fait pas partie du programme de fid�lit�.
	//modifierPoints(calculerPoints(billet));
}




/*******************************************************************************************
 * Methode: operator==
 * Description: permet de comparer un membre avec un nom
 * Param�tres: const string& : nom
 * Type de retour: bool
 ********************************************************************************************/
bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}





/*******************************************************************************************
 * Methode: operator==
 * Description: permet de comparer un nom avec un membre
 * Param�tres: const string& : nom , Membre& : membre
 * Type de retour: bool
 ********************************************************************************************/
bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}




/*******************************************************************************************
 * Methode: operator=
 * Description: permet d'affecter un memre existant � un autre ( existant aussi), tout en �crasant
 *				le contenu de ses attributs et les ceux du membre pass� en param�tre
 * Param�tres: const Membre& membre : membre
 * Type de retour: Membre
 ********************************************************************************************/
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;
		typeMembre_ = membre.typeMembre_;


		for (int i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		for ( int i = 0; i < membre.billets_.size(); i++) {
			billets_.push_back(new Billet(*membre.billets_[i]));
		}
	}

	return *this;
}


/*******************************************************************************************
 * Methode: operator<<
 * Description: permet d'afficher les informations d'un membre
 * Param�tres: ostream& : os
 *			   const Membre& : membre
 * Type de retour: ostream
 ********************************************************************************************/
ostream& operator<<(ostream& o, const Membre& membre) 
{
	o << setfill(' ');
	o << "- Membre " << membre.nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	for (unsigned int i = 0; i < membre.billets_.size(); i++) {
		if (membre.billets_[i]->getTypeBillet()  == Flight_Pass) {
			o << *static_cast<FlightPass*>(membre.billets_[i]);
		}
		else if (membre.billets_[i]->getTypeBillet() == Billet_Base) {
			o << *membre.billets_[i];
		}
		else if (membre.billets_[i]->getTypeBillet() == Billet_Regulier) {
			o << *static_cast<BilletRegulier*>(membre.billets_[i]);
		}
	}
	

	return o << endl;
}
