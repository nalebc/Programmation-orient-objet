#include "coupon.h"

Coupon::Coupon()
{
	code_ = "default";
	rabais_ = 0;
	cout_ = 0;
}

Coupon::Coupon(const string& code, double rabais, int cout)
{
	code_ = code;
	rabais_ = rabais;
	cout_ = cout;
}

Coupon::~Coupon()
{
}

string Coupon::getCode()
{
	return code_;
}

double Coupon::getRabais()
{
	return rabais_;
}

int Coupon::getCout()
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

void Coupon::afficherCoupon()
{
	cout << "affichage coupon" << endl;
}

