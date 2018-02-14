#include <exception>
#include <iostream>
using namespace std;

#include "../defs/Climat.h"


int Metier::Climat::ajouterClimat( int aSalle) {
	cout<<"ajouter climat"<<endl;
}

void Metier::Climat::supprimer() {
	throw "Not yet implemented";
}

void Metier::Climat::getDateHeureReleve(char dateHeureReleve[4]) {
	for (int i = 0; i<4 ; i++)
	{
		dateHeureReleve[i]=_dateHeureReleve[i];
	}
}

float Metier::Climat::getTemperature() {
	return this->_temperature;
}

int Metier::Climat::getHumidity() {
	return this->_humidity;
}

int Metier::Climat::getGaz() {
	return this->_gaz;
}

Metier::Climat::Climat(float temperature, int humidity, int gaz, char dateHeureReleve[4]){
;
	 _temperature=temperature;
	 _humidity=humidity;
	_gaz=gaz;

	for (int i = 0; i<4 ; i++)
	{
		_dateHeureReleve[i]=dateHeureReleve[i];
	}

}

