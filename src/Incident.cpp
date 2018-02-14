#include <exception>
#include <string>
#include <iostream>
using namespace std;

#include "../defs/Incident.h"
#include "../defs/NatureInfo.h"


string Metier::Incident::getTypeIncident() {
	return _type;
}

void Metier::Incident::setTypeDate(string type, char aDate[4]) {
	_type=type;
	for (int i = 0; i<4 ; i++)
	{
		_dateHeureIncident[i]=aDate[i];
	}
	cout<<"Ecriture dans le fichier"<<endl;
}

char Metier::Incident::getCode() {
	return this->_code;
}

void Metier::Incident::finir(char aDate[4]) {
cout<<"finir Incident"<<endl;
	etat=true;
	for (int i = 0; i<4 ; i++)
	{
		_dateFinIncident[i]=aDate[i];
	}

cout<<"finir _dateFinIncident"<<endl;
	cout << "Fin d'incident " << _type << " code : " <<  (int) _code<<" écrite dans le fichier  à : " <<endl ;
	cout<< (int)*_dateFinIncident << " " <<(int)*(_dateFinIncident+1) << " " <<(int)*(_dateFinIncident+2) << " " <<(int)*(_dateFinIncident+3) <<endl;
}

void Metier::Incident::supprimer() {
	cout<<"Incident type " << _type  << "et fini le " << (int)*_dateFinIncident << "/" <<(int)*(_dateFinIncident+1) << ";" <<(int)*(_dateFinIncident+2) << "h" <<(int)*(_dateFinIncident+3) << "mn est supprimé du fichier"<<endl; ;
}


bool Metier::Incident::getEtat() {
	return this->etat;
}

void Metier::Incident::setDebutTransmis(bool aDebutTransmis) {
	this->_debutTransmis = aDebutTransmis;
}

bool Metier::Incident::isDebutTransmis() {
	return this->_debutTransmis;
}

void Metier::Incident::setFinTransmise(bool aFinTransmise) {
	this->_finTransmise = aFinTransmise;
}

bool Metier::Incident::isFinTransmise() {
	return this->_finTransmise;
}

void Metier::Incident::getDateHeureIncident(char dateHeureIncident[4]) {
	for (int i = 0; i<4 ; i++)
	{
		dateHeureIncident[i]=_dateHeureIncident[i];
	}
}

void Metier::Incident::getDateFinIncident(char dateHeureFinIncident[4]) {

	for (int i = 0; i<4 ; i++)
	{
		dateHeureFinIncident[i]=_dateFinIncident[i];
	}
}

Metier::Incident::Incident(string type, char dateHeureIncident [4],char  codeIncident)
{
	etat = false;
	_debutTransmis = false;
	_finTransmise = false;
	_type=type;
	for (int i = 0; i<4 ; i++)
	{
		_dateHeureIncident[i]=dateHeureIncident[i];
	}
	_code=codeIncident;
	for (int i = 0; i<4 ; i++)
	{
		_dateFinIncident[i]=0;
	}

	cout << "Incident " << _type << " créé à : " <<endl ;
	cout<< (int)*_dateHeureIncident << " " <<(int)*(_dateHeureIncident+1) << " " <<(int)*(_dateHeureIncident+2) << " " <<(int)*(_dateHeureIncident+3) <<endl;
}


