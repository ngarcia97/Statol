#include <string>
using namespace std;

#include "../defs/TClimat.h"

Communication::TClimat::TClimat(string tclimat) {
	_valeur = tclimat;
}
void Communication::TClimat::setValeur(string adresse)
{
	_valeur = adresse;
}
string Communication::TClimat::getValeur()
{
	return _valeur;
}
