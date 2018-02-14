#include <exception>
#include <string>
using namespace std;

#include "../defs/ProtocoleCapteurs.h"
Communication::ProtocoleCapteurs::ProtocoleCapteurs() {
	_adresse = "668AC";
	_separateur = '/';
	_fin = '*';
	_debut = '$';
	_aBSENCETRAME = -1;
}

