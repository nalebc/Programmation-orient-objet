/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe C�T�-MORNEAULT
 */

#include "billet.h"




 /****************************************************************************
 * Methode: Billet
 * Description: Constructeur par default
 * Param�tres: aucun
 * Type de retour: aucun
 ****************************************************************************/
Billet::Billet() :
	pnr_(""),
	nomPassager_(""),
	prix_(0),
	od_(""),
	tarif_(TarifBillet::Economie),
	typeBillet_(Billet_Base)
{
}




/****************************************************************************
 * Methode: Billet
 * Description: Constructeur par param�tres
 * Param�tres: aucun
 * Type de retour: aucun
 ****************************************************************************/
Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet) :
	pnr_(pnr),
	nomPassager_(nomPassager),
	prix_(prix),
	od_(od),
	tarif_(tarif),
	typeBillet_(typeBillet)

{
}





/****************************************************************************
 * Methode: ~Billet
 * Description: Desctructeur
 * Param�tres: aucun
 * Type de retour: aucun
 ****************************************************************************/
Billet::~Billet()
{
}



/****************************************************************************
 * Methode: getTypeBillet
 * Description: r�cup�re typeBillet_
 * Param�tres: aucun
 * Type de retour: TypeBillet
 ****************************************************************************/
TypeBillet Billet::getTypeBillet() const
{
	return typeBillet_;
}



/****************************************************************************
 * Methode: getPnr
 * Description: r�cup�re pnr_
 * Param�tres: aucun
 * Type de retour: string
 ****************************************************************************/
string Billet::getPnr() const
{
	return pnr_;
}



/****************************************************************************
 * Methode: getNomPassager
 * Description: r�cup�re nomPassager_
 * Param�tres: aucun
 * Type de retour: string
 ****************************************************************************/
string Billet::getNomPassager() const
{
	return nomPassager_;
}



/****************************************************************************
 * Methode: getPrix
 * Description: r�cup�re prix_
 * Param�tres: aucun
 * Type de retour: double
 ****************************************************************************/
double Billet::getPrix() const
{
	return prix_;
}




/****************************************************************************
 * Methode: getOd
 * Description: r�cup�re od_
 * Param�tres: aucun
 * Type de retour: string
 ****************************************************************************/
string Billet::getOd() const
{
	return od_;
}




/****************************************************************************
 * Methode: getTarif
 * Description: r�cup�re tarif_
 * Param�tres: aucun
 * Type de retour: TarifBillet
 ****************************************************************************/
TarifBillet Billet::getTarif() const
{
	return tarif_;
}





// Setters
/****************************************************************************
 * Methode: setPnr
 * Description: modifier pnr_
 * Param�tres: pnr ( const string&)
 * Type de retour: aucun
 ****************************************************************************/
void Billet::setPnr(const string& pnr)
{
	pnr_ = pnr;
}




/****************************************************************************
 * Methode: setNomPassager
 * Description: modifier nomPassager_
 * Param�tres: nomPassager ( const string&)
 * Type de retour: aucun
 ****************************************************************************/
void Billet::setNomPassager(const string& nomPassager)
{
	nomPassager_ = nomPassager;
}



/****************************************************************************
 * Methode: setPrix
 * Description: modifier prix_
 * Param�tres: prix ( const string&)
 * Type de retour: aucun
 ****************************************************************************/
void Billet::setPrix(double prix)
{
	prix_ = prix;
}




/****************************************************************************
 * Methode: setOd
 * Description: modifier od_
 * Param�tres: od ( const string&)
 * Type de retour: aucun
 ****************************************************************************/
void Billet::setOd(const string& od)
{
	od_ = od;
}




/****************************************************************************
 * Methode: setTarif
 * Description: modifier tarif_
 * Param�tres: tarif ( TarifBillet)
 * Type de retour: aucun
 ****************************************************************************/
void Billet::setTarif(TarifBillet tarif)
{
	tarif_ = tarif;
}

/****************************************************************************
 * Methode: setTypeBillet
 * Description: modifier typeBillet_
 * Param�tres: typeBillet ( TypeBillet)
 * Type de retour: aucun
 ****************************************************************************/
void Billet::setTypeBillet(TypeBillet typeBillet)
{
	typeBillet_ = typeBillet;
}




/****************************************************************************
 * Methode: formatTarif
 * Description:  converti le type de tarif tir� de l�enum TarifBillet � la
 *				 cha�ne de caract�re correspondante.
 * Param�tres: tarif ( TarifBillet)
 * Type de retour: string
 ****************************************************************************/
string Billet::formatTarif(TarifBillet tarif) const
{
	switch (tarif)
	{
		case TarifBillet::Economie:
			return "Economie";
		case TarifBillet::PremiumEconomie:
			return "Premium economie";
		case TarifBillet::Affaire:
			return "Affaire";
		case TarifBillet::Premiere:
			return "Premiere";
		default:
			return "";
	}
}


/****************************************************************************
* Surcharge de l'operateur <<
* Description: Affiche un Billet
* Param�tres:	- ostream : os
*				- Billet : billet
* Type de retour: ostream
****************************************************************************/
ostream& operator<<(ostream& o, const Billet& billet)
{
	o << "\t\t- Billet " << billet.pnr_ << " (Classe : " << billet.formatTarif(billet.tarif_) << ")" << endl;
	o << left << "\t\t\t" << setw(11) << "- Passager " << ": " << billet.nomPassager_ << endl;
	o << "\t\t\t" << setw(11) << "- Prix" << ": " << billet.prix_ << "$" << endl;
	o << "\t\t\t" << setw(11) << "- Trajet" << ": " << billet.od_ << endl;

	return o;
}
