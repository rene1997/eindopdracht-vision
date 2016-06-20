#pragma once

#include <string>
using namespace std;


class Persoon
{
public:
	Persoon(string naam, int geboorteJaar);
	void wijzigPartner(string * naam);
	void voegKindToe(string * naam);
	~Persoon();
private: 
	string naam;
	int geboortejaar;
	string *partner;
	string *kinderen;
	int aantalKinderen;
	int maxAantalkinderen;
};

