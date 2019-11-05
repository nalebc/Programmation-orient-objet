/********************************************
* Titre: Travail pratique #5 - GestionnaireGenerique.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#pragma once

#include <algorithm>
#include "foncteur.h"

using namespace  std;

/*
    class GestionnaireGenerique

    Méthodes :
   
    void ajouter(const T& t);
    int getNombreElements() const;
 
    Attributs :
    C conteneur_;
*/

/*              
	* T   = pair<string, Membre*> ou Coupon*; 
	* Conteneur   = map<string, Membre*> ou vector<Coupon*>; 
	* FoncteurAjouter = AjouterMembre ou AjouterCoupon
*/
template<typename C, typename T, typename FoncteurAjouter>

class GestionnaireGenerique
{
public:
	C getConteneur() const;
	void ajouter(const T& t);
	int getNombreElements() const;

protected: 
	C conteneur_;
	

};

template<typename C, typename T, typename FoncteurAjouter>
C GestionnaireGenerique<C, T, FoncteurAjouter>::getConteneur() const
{
	 return conteneur_;
}

 template<typename C, typename T, typename FoncteurAjouter>
  void GestionnaireGenerique<C, T, FoncteurAjouter>::ajouter(const T & t)
 {
	//  insert(conteneur_.end()--, t
	 FoncteurAjouter foncteur = FoncteurAjouter(conteneur_);
	 foncteur(t);
	  
	  
	  
 }

  template<typename C, typename T, typename FoncteurAjouter>
  int GestionnaireGenerique<C, T, FoncteurAjouter>::getNombreElements() const
 {
	 return conteneur_.size() ;
 }
