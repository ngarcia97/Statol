#include <exception>
#include <string>
using namespace std;

#include "../defs/Adresse.h"
Communication::Adresse::Adresse(string adresse) {
	_valeur = adresse;
}
void Communication::Adresse::setValeur(string adresse)
{
	_valeur = adresse;
}
string Communication::Adresse::getValeur()
{
	return _valeur;
}

