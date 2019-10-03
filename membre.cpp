/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

//a changer
Membre::Membre() :
	nom_(""), typeMembre_(Membre_Regulier)
{
}

//a changer
Membre::Membre(const string& nom, TypeMembre typeMembre) :
	nom_(nom), typeMembre_ (typeMembre)
{
}
//a changer
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

Membre::~Membre()
{
	for (int i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}

string Membre::getNom() const
{
	return nom_;
}

TypeMembre Membre::getTypeMembre() const
{
	return typeMembre_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}


void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

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
			cout << "Erreur" << endl;
	
}

// a changer
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



	//inutile, cette classe ne fait pas partie du programme de fidèlité.
	//modifierPoints(calculerPoints(billet));
}



bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}

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

// a changer
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
