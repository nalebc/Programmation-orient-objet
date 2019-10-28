#include "billet.h"

Billet::Billet()
{
}

Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	pnr_ = pnr;
	nomPassager_ = nomPassager;
	prix_ = prix;
	od_ = od;
	tarif_ = tarif;
	dateVol_ = dateVol;
}

Billet::~Billet()
{
}

string Billet::getPnr()
{
	return pnr_;
}

string Billet::getNomPassager()
{
	return nomPassager_;
}
double Billet::getPrix()
{
	return prix_;
}
string Billet::getOd()
{
	return od_;
}
TarifBillet Billet::getTarif()
{
	return tarif_;
}
string Billet::getDateVol()
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

string Billet::formatTarif(TarifBillet tarif)
{
	switch (tarif)
	{
	case TarifBillet::Economie: return "Economie";
		break;
	case TarifBillet::PremiumEconomie:return "Premium economie";
		break;
	case TarifBillet::Affaire:return "Affaire";
		break;
	case TarifBillet::Premiere:return "Premiere";
		break;
	}
}

void Billet::afficherBillet()
{
	cout << "test Billet" << endl;
}
