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

	cout << "Persoon " << this->naam << "toegevoegd " << endl;
	cout << "Geboortejaar: " << this->geboortejaar << endl;
}

void Persoon::wijzigPartner(string * naam) {

	this->partner = naam;

	cout << endl << "partner aan " << this->naam << " toegevoegd";
	cout << endl << " partner is: " << *this->partner << endl;
}

void Persoon::voegKindToe(string * naam) {
	this->kinderen[aantalKinderen] = *naam;
	aantalKinderen++;

	if (aantalKinderen >= maxAantalkinderen) {
		maxAantalkinderen *= 2;
		cout << "geheugen uitbreiden naar " << maxAantalkinderen << endl;
		string* temp = new string[maxAantalkinderen];
		for (int i = 0; i < aantalKinderen; i++) {
			temp[i] = kinderen[i];
		}
		delete[] kinderen;
		kinderen = temp;
	}

	cout << "kind toegevoegd:" << endl << "kinderen: " << endl;

	for (int i = 0; i < aantalKinderen; i++) {
		cout << kinderen[i] << " ";
	}

	cout << endl;
}

Persoon::~Persoon()
{
	delete kinderen;
	delete partner;
}

Persoon& Persoon::operator=(Persoon &persoon) {
	cout << "toekenningsoperator = ";
	this->naam = persoon.naam;
	this->geboortejaar = persoon.geboortejaar;
	this->partner = persoon.partner;
	this->aantalKinderen = persoon.aantalKinderen;
	this->maxAantalkinderen = persoon.maxAantalkinderen;
	this->kinderen = new string[maxAantalkinderen];
	for (int i = 0; i < aantalKinderen; i++) {
		this->kinderen[i] = persoon.kinderen[i];
	}
	return *this;
}

void Persoon::printPersoon() {
	cout << "naam: " << naam << " geboortejaar " << geboortejaar << endl;


}
