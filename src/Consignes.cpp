#include <exception>
#include <iostream> 
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#include "../defs/Consignes.h"


int Metier::Consignes::lireConsignes(int aNumero) {
	//string tempBuffMin,tempBuffMAX,humBuffMin,humBuffMAX,gazBuff;

	std::string ligne[6] = "";
	
	std::string line = "";
	std::string separateur = ";";
	int i = 0;
	
	std::string::size_type sz;
	
	ifstream tampon("Consignes.csv", ios::in);

	while(getline(tampon, line))	{
		
		ligne[i] = line;
		i++;
	
	}
	
	std::cout << ligne[aNumero-1] << endl;
	
	std::string salle = ligne[aNumero-1].substr(0, ligne[aNumero-1].find(separateur));
	ligne[aNumero-1] = ligne[aNumero-1].erase(0, ligne[aNumero-1].find(separateur)+1);
	cout << "Numero de la salle : " << salle << endl;
	
	std::string adresse = ligne[aNumero-1].substr(0, ligne[aNumero-1].find(separateur));
	ligne[aNumero-1] = ligne[aNumero-1].erase(0, ligne[aNumero-1].find(separateur)+1);
	cout << "Adresse du capteur : " << adresse << endl;
	
	std::string sTempMin = ligne[aNumero-1].substr(0, ligne[aNumero-1].find(separateur));
	ligne[aNumero-1] = ligne[aNumero-1].erase(0, ligne[aNumero-1].find(separateur)+1);
	float tempMin = std::stof(sTempMin,&sz);
	cout << "Temperature minimale souhaitée : " << tempMin << endl;
	
	std::string sTempMax = ligne[aNumero-1].substr(0, ligne[aNumero-1].find(separateur));
	ligne[aNumero-1] = ligne[aNumero-1].erase(0, ligne[aNumero-1].find(separateur)+1);
	float tempMax = std::stof(sTempMax,&sz);
	cout << "Temperature maximale souhaitée : " << tempMax << endl;
	
	std::string sHumMin = ligne[aNumero-1].substr(0, ligne[aNumero-1].find(separateur));
	ligne[aNumero-1] = ligne[aNumero-1].erase(0, ligne[aNumero-1].find(separateur)+1);
	float humMin = std::stof(sHumMin,&sz);
	cout << "Humidite minimale souhaitée : " << humMin << endl;
	
	std::string sHumMax = ligne[aNumero-1].substr(0, ligne[aNumero-1].find(separateur));
	ligne[aNumero-1] = ligne[aNumero-1].erase(0, ligne[aNumero-1].find(separateur)+1);
	float humMax = std::stof(sHumMax,&sz);
	cout << "Humidite maximale souhaitée : " << humMax << endl;
	
	std::string sGazSeuil = ligne[aNumero-1].substr(0, ligne[aNumero-1].find(separateur));
	ligne[aNumero-1] = ligne[aNumero-1].erase(0, ligne[aNumero-1].find(separateur));
	float gazSeuil = std::stof(sGazSeuil,&sz);
	cout << "Seuil de gaz souhaité : " << gazSeuil << endl;
	
	tampon.close();
	
	
	return 1;
}

int Metier::Consignes::getTempHumidGaz(float& aTempMin, float& aTempMAX, int& aHumidMin, int& aHumidMax, int& aGaz) {
	cout << "getTempHumidGaz" << endl;
	aTempMin=_temperatureMin;
	aTempMAX=_temperatureMax;
	aHumidMin=_humiditeMin;
	aHumidMax=_humiditeMax;
	aGaz=_gaz;

	return 1;
}

void Metier::Consignes::setTemperatureMin(float tMin) {
	_temperatureMin=tMin;
}


Metier::Consignes::Consignes() {
	_temperatureMin = 18;
	_temperatureMax = 22;
	_humiditeMin = 40;
	_humiditeMax = 70;
	_gaz = 550;
}


