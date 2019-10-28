/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe C�T�-MORNEAULT
 */

#include "billet.h"

Billet::Billet() :
	pnr_(""),
	nomPassager_(""),
	prix_(0),
	od_(""),
	tarif_(TarifBillet::Economie),
	dateVol_("")
{
}

Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol) :
	pnr_(pnr),
	nomPassager_(nomPassager),
	prix_(prix),
	od_(od),
	tarif_(tarif),
	dateVol_(dateVol)
{
}

Billet::~Billet()
{
}

string Billet::getPnr() const
{
	return pnr_;
}

string Billet::getNomPassager() const
{
	return nomPassager_;
}

double Billet::getPrix() const
{
	return prix_;
}

string Billet::getOd() const
{
	return od_;
}

TarifBillet Billet::getTarif() const
{
	return tarif_;
}

string Billet::getDateVol() const
{
	return dateVol_;
}

void Billet::setPnr(const string& pnr)
{
	pnr_ = pnr;
}

void Billet::setNomPassager(const string& nomPassager)
{
	nomPassager_ = nomPassager;
}

void Billet::setPrix(double prix)
{
	prix_ = prix;
}

void Billet::setOd(const string& od)
{
	od_ = od;
}

void Billet::setTarif(TarifBillet tarif)
{
	tarif_ = tarif;
}

void Billet::setDateVol(const string& dateVol)
{
	dateVol_ = dateVol;
}

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

// TODO: Remplacer cette methode par l'operateur <<
void Billet::afficherBillet() const
{
	cout << "\t\t- Billet " << pnr_ << " (Classe : " << formatTarif(tarif_) << ")" << endl;
	cout << left << "\t\t\t" << setw(11) << "- Passager " << ": " << nomPassager_ << endl;
	cout << "\t\t\t" << setw(11) << "- Prix" << ": " << prix_ << "$" << endl;
	cout << "\t\t\t" << setw(11) << "- Trajet" << ": " << od_ << endl;
	cout << "\t\t\t" << setw(11) << "- Vol le" << ": " << dateVol_ << endl;
}

ostream& operator<<(ostream& o, const Billet& billet)
{
	// TODO: insert return statement here
	o << "\t\t- Billet " << billet.pnr_ << " (Classe : " << billet.formatTarif(billet.tarif_) << ")" << endl
	<< left << "\t\t\t" << setw(11) << "- Passager " << ": " << billet.nomPassager_ << endl
	<< "\t\t\t" << setw(11) << "- Prix" << ": " << billet.prix_ << "$" << endl
	<< "\t\t\t" << setw(11) << "- Trajet" << ": " << billet.od_ << endl
	<< "\t\t\t" << setw(11) << "- Vol le" << ": " << billet.dateVol_ << endl;
	return o;
}
