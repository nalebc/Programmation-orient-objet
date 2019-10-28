/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "coupon.h"

Coupon::Coupon() : 
	code_(""),
	rabais_(0),
	cout_(0)
{
}

Coupon::Coupon(const string& code, double rabais, int cout) :
	code_(code),
	rabais_(rabais),
	cout_(cout)
{
}

Coupon::~Coupon()
{
}

string Coupon::getCode() const
{
	return code_;
}

double Coupon::getRabais() const
{
	return rabais_;
}

int Coupon::getCout() const
{
	return cout_;
}

void Coupon::setCode(const string& code)
{
	code_ = code;
}

void Coupon::setRabais(double rabais)
{
	rabais_ = rabais;
}

void Coupon::setCout(int cout)
{
	cout_ = cout;
}

bool Coupon::operator<(const Coupon& coupon)
{
	return (this->rabais_ < coupon.rabais_);
}

bool Coupon::operator>(const Coupon& coupon)
{
	return (this->rabais_>coupon.rabais_);
}


// TODO: Remplacer cette methode par l'operateur <<
void Coupon::afficherCoupon() const
{
	cout << "\t\t- Coupon " << code_ << ". Rabais : " << rabais_ << "." << endl;
}
ostream& operator<<(ostream& o,const Coupon& coupon)
{
	o << "\t\t- Coupon " << coupon.code_ << ". Rabais : " << coupon.rabais_ << "." << endl;
	return o;
}
