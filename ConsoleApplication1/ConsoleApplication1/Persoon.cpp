#include "Persoon.h"

#include <string>
#include <iostream>
using namespace std;



Persoon::Persoon(string naam, int geboorteJaar)
{
	this->naam = naam;
	this->geboortejaar = geboorteJaar;
	this->kinderen = new string[2];
	this->maxAantalkinderen = 2;
	this->aantalKinderen = 0;

	cout << "Persoon " << this->naam << "toegevoegd" << endl;
	cout << "Geboortejaar: " << this->geboortejaar <<endl;
}

void Persoon::wijzigPartner(string * naam) {
	
	this->partner = naam;
}

void Persoon::voegKindToe(string * naam) {
	this->kinderen[aantalKinderen] = *naam;
	aantalKinderen++;
	cout << "kind toegevoegd:" << endl << "kinderen:" << endl;

	for (int i = 0; i < aantalKinderen; i++) {
		cout << kinderen[i];
	}

}

Persoon::~Persoon()
{
}
