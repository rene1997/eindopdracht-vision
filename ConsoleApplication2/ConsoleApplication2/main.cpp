#include <cstdio>
#include "Persoon.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	Persoon * p1 = new Persoon("pietje", 1990);
	string * partner = new string("vrouwtje");
	p1->wijzigPartner(partner);
	
	string * kind1 = new string("kind1");
	p1->voegKindToe(kind1);
	string * kind2 = new string("kind2");
	p1->voegKindToe(kind2);

	string * kind3 = new string("kind3");
	p1->voegKindToe(kind3);

	Persoon * p2 = p1;

	p2->printPersoon();
	
	int i;
	cin >> i;
}



