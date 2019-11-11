/********************************************
* Titre: Travail pratique #5 - foncteur.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/
#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "coupon.h"
#include "membrePremium.h"

class AjouterCoupon
{
//TODO
	public:
		AjouterCoupon(vector<Coupon*>& coupon) :conteneur_(coupon)
		{};
		void operator()(Coupon* coupon)
		{
			auto c = find(begin(conteneur_), end(conteneur_),coupon);
			if (c == end(conteneur_)) //ou c==end(conteneur_)
			{
				conteneur_.push_back(coupon);
			}
		}
	private:
		vector<Coupon*>& conteneur_;
};


class AjouterMembre
{
//TODO
	public:
		AjouterMembre(map<string, Membre*>& map) :conteneur_(map)
		{};
		void operator()(pair<string, Membre*> pair)
		{
			conteneur_.emplace(pair.first, pair.second);
		}

	private:
		map<string, Membre*>& conteneur_;
};

class IntervallePrixBillet
{
//  TODO
	public:
		IntervallePrixBillet(double borneInf, double borneSup) :borneInf_(borneInf), borneSup_(borneSup)
		{};
		bool operator()(Billet* billet)
		{
			return billet->getPrix() > borneInf_ && billet->getPrix() < borneSup_;
		}
	private:
		double borneInf_;
		double borneSup_;

};