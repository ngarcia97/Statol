#include <exception>
#include <stdexcept>      // std::invalid_argument
#include <cstring>
#include <map>
#include <iostream>
#include <unistd.h>
using namespace std;


#include "../defs/C_Capteur.h"
//#include "../defs/serialib.h"
#include "../defs/ProtocoleCapteurs.h"
#include "../defs/Adresse.h"
#include "../defs/TClimat.h"
#include "../defs/serialib.h"

using namespace Communication;

void Communication::C_Capteur::lire(string &trame) {
    	serialib LS;                                                            
   	int Ret; 
	char Buffer[128];                                                               
	// Ouverture du port série à 115200 bauds

   	Ret=LS.Open(UART2_RXD,115200);

		// Lire un maximum de 128 caractères avec un timeout de 5 secondes
		//Le caractère final de la chaîne de caractères doit être un retour à la ligne ('\n')
    	Ret=LS.ReadString(Buffer,'\n',128,15000);

	trame = string(Buffer);

	ajouterTrameASalve(trame);
	LS.Close();
}

int Communication::C_Capteur::ajouterTrameASalve(string trame) {
	string lAdresse;
	long adresseVerif = 0;
	string leClimat;
	lAdresse = trame.substr(trame.find(_debut)+1,trame.find(_separateur)-1);
	try 
	{
		adresseVerif = std::stol (lAdresse,NULL,10);

	}
	catch (const std::invalid_argument& ia){
		return -1;
	}
	trame = trame.erase(0,trame.find(_separateur) + 1); 
	leClimat=trame.substr(0,trame.find(_fin));
	_salve.insert(std::pair<string,string>(lAdresse,leClimat));
}

map<string, string>  Communication::C_Capteur::getSalve()
{
	return _salve;
}

int Communication::C_Capteur::extraireTrame(string aAdresse, string& aTrame) {
//cout<<aAdresse<<endl;
	if (_salve.empty()) return TRAMEINEXISTANTE;
	else 
	{
		for (std::map<string, string> ::iterator it=_salve.begin(); it!=_salve.end(); ++it)
		{
			size_t found = it->first.find(aAdresse);
		cout<< it->second <<endl;
    			if (found!=std::string::npos) 
			{
				aTrame=it->second ;
			        return OK;
			}
		}
		return TRAMEINEXISTANTE;
	}
}

int Communication::C_Capteur::remettreAZeroLaSalve() {
	_salve.erase(_salve.begin(),_salve.end());
}

/// Création d'un thread à l'aide de la méthode lire
thread Communication::C_Capteur::activerReception(){
	return std::thread([this] {

		string trame;
	do{

		lire(trame);
		
	}while(1);
		}
	
		);
}

Communication::C_Capteur::C_Capteur() {
	_port = "/dev/ttyO2";

}

