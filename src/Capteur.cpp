#include <exception>
#include <string>
#include <iostream>

using namespace std;

#include "../defs/Capteur.h"


string trameCherchee;

int Metier::Capteur::getTempHumid(float& aTemperature, int& aHumidity) {
//	cout<<"entree dans gethumid"<<endl;
	int error = -1;
	error = leCapteur->extraireTrame(_adresse, trameCherchee);
//	cout<<"error = leCapteur->: "<<error <<endl;
	if (error <=0) return error;
	//cout<<"la trame est : "<<trameCherchee<<endl;
	string temp = trameCherchee.substr(0, trameCherchee.find(_separateur));
	trameCherchee = trameCherchee.erase(0, trameCherchee.find(_separateur) + 1);
	float tttp = stof(temp);
	tttp = tttp * 250 / 1023 - 20;
	aTemperature = tttp;
	string hum = trameCherchee.substr(0, trameCherchee.find(_separateur));
	float toto = stof(hum);
	toto = (toto / 1023 - 0.16) / 0.0062;	// Conversion liée au convertisseur AN de l'arduino : 5/1023
											// Conversion liée au capteur (voir documentation) : (tttp /5 - 0.16) / 0.0062

	toto = toto / (1.0546 - 0.00216*tttp);	// Compensation en température (voir documentation) : /(1.0546-0.00216*tttp)
	aHumidity = toto;
	return OK;
}

int Metier::Capteur::getGaz(int& aValeur) {
	string gazTab;

	int error = leCapteur->extraireTrame(_adresse, trameCherchee);
	if (error <=0) return error;
	gazTab=trameCherchee.substr(trameCherchee.find_last_of(_separateur) +1,trameCherchee.size() -1);
	aValeur=stoi(gazTab,NULL,10);
	return OK;
}


void Metier::Capteur::supprimerEnregistrement() {
	leCapteur->remettreAZeroLaSalve();

}

Metier::Capteur::Capteur(string adresse,Communication::C_Capteur *unCapteur)
{
    leCapteur=unCapteur;
	_adresse= adresse;
}

