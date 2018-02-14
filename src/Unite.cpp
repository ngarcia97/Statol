#include <exception>
#include <list>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

#include "../defs/Unite.h"
#include "../defs/Information.h"
#include "../defs/Consignes.h"
#include "../defs/Capteur.h"
#include "../defs/Incident.h"
#include "../defs/Climat.h"
#include "../defs/NatureInfo.h"
#include "../defs/C_Informations.h"
#include "../defs/C_Capteur.h"

int Metier::Unite::comparerTemperature(float aReleve, float aTempMin, float aTempMAX) {
	
	if (aReleve<aTempMin) return Communication::NatureInfo::CL_TEMPINCIDENT_MIN;
	if (aReleve>aTempMAX) return Communication::NatureInfo::CL_TEMPINCIDENT_MAX;
	if ((aReleve>-20) && (aReleve<50)) return Communication::NatureInfo::CL_TEMP;
	else return Communication::NatureInfo::CL_TEMP_DEFECTUEUX;
}

int Metier::Unite::comparerHumidite(int aReleve, int aHumidMin, int aHumidMAX) {
	if (aReleve<aHumidMin) return Communication::NatureInfo::CL_HUMINCIDENT_MIN;
	if (aReleve>aHumidMAX) return Communication::NatureInfo::CL_HUMINCIDENT_MAX;
	if ((aReleve>5) && (aReleve<95)) return Communication::NatureInfo::CL_HUM;
	else return Communication::NatureInfo::CL_HUM_DEFECTUEUX;
}

int Metier::Unite::comparerGaz(int aReleve, int aSeuil) {
	if (aReleve>aSeuil) return Communication::NatureInfo::CL_QAIRINCIDENT;
	if ((aReleve>10) && (aReleve<2000)) return Communication::NatureInfo::CL_QAIR;
	else return Communication::NatureInfo::CL_QAIR_DEFECTUEUX;
}
 
void Metier::Unite::ajouterIncident(string type, char  codeIncident) {

	if (!verifierPresenceIncident(type)) 	
	{
		creerIncident(type,codeIncident);
		incidents.back()->setTypeDate(type, _dateHeureCourante);
	}
}

int Metier::Unite::verifierClimatSalle(int  codeIncident[3]) {
	float temperature;
	int humidity, gaz,erreur;
	float tempMin, tempMAX;
	int humMin, humMAX, seuilGaz;
	erreur=0;
	consignes->lireConsignes(1);
	consignes->getTempHumidGaz(tempMin,tempMAX,humMin,humMAX,seuilGaz);
	do {	
		erreur = capteur->getTempHumid(temperature,humidity);
	}
	while (erreur<=0);	
	capteur->getGaz(gaz);
	codeIncident[0]=comparerTemperature(temperature, tempMin, tempMAX);
	if (humMAX>10) codeIncident[1]= comparerHumidite(humidity, humMin, humMAX);
	else codeIncident[1]= Communication::NatureInfo::CL_HUMNONINSTAL;
	if (seuilGaz>10) codeIncident[2]= comparerGaz(gaz, seuilGaz);
	else codeIncident[2]= Communication::NatureInfo::CL_QAIRNONINSTAL;
	horodater(_dateHeureCourante);
	climats.push_back(new Climat(temperature, humidity, gaz, _dateHeureCourante));
	climats.back()->ajouterClimat(_numero); 
	return 1;
}

/*
* Méthode permettant de vérifier qu'un incident détecté est déjà enregistré ou pas.
* Si un enreistrement est déjà enregistré, la méthode retourne true.
* Sinon, elle retourne false.
*/

bool Metier::Unite::verifierPresenceIncident(string type) {
	size_t position;
	if (incidents.empty()) {return false;}
	else
		for(vector<Incident*>::iterator it=incidents.begin(); it!=incidents.end(); ++it)
		{
		 	position=  ((*it)->getTypeIncident()).find(type);  
			if (position!= std::string::npos) 	
				if ((*it)->getEtat() == false) return true;
						
		}
	return false;

}

void Metier::Unite::creerIncident(string type,char  codeIncident) {

	incidents.push_back(new Incident(type, _dateHeureCourante, codeIncident));
}

void Metier::Unite::finirIncident(string type) {
	if (verifierPresenceIncident(type)) 
		for(vector<Incident*>::iterator it=incidents.begin(); it!=incidents.end(); ++it)
		{
		      	if (((*it)->getTypeIncident()).find(type)!= std::string::npos) 	
			{
				(*it)->finir(_dateHeureCourante);
				(*it)->setFinTransmise(false);
			}
						
		}
}

void Metier::Unite::supprimerIncident(char heureReleve[4]) {
	char dateHeureIncident[4];
	if (!incidents.empty())
		for(vector<Incident*>::iterator it=incidents.begin(); it!=incidents.end(); ++it)
		{


			(*it)->getDateFinIncident(dateHeureIncident);
			if ((dateHeureIncident[0] ==heureReleve[0]) &&
			    (dateHeureIncident[1] ==heureReleve[1]) &&
			    (dateHeureIncident[2] ==heureReleve[2]) &&
			    (dateHeureIncident[3] ==heureReleve[3]) )
			     	if ((*it)->isFinTransmise()) 
				{
					(*it)->supprimer();
					incidents.erase(it);
				}
		}
}

void Metier::Unite::transmettreInformations(Communication::C_Informations *laCommunication) {
	char heureReleve[4];
	char dateHeureIncident[4];
	list<Incident*> incidentsSalle;
	Communication::Information lInformation;
	if (!climats.empty())
		for(vector<Climat*>::iterator it=climats.begin(); it!=climats.end(); ++it)
		{
			(*it)->getDateHeureReleve(heureReleve);
			extraireIncidentsA(heureReleve, incidentsSalle);
			associerIncidentDonneeClimat(*it, incidentsSalle, lInformation);
			laCommunication->ecrire( lInformation);
			supprimerIncident(heureReleve);
			supprimerreleve(it);	
			it--;
		}
}
/**
* horodater permet de récupérer l'heure actuelle du superviseur.
* Le système sera mis à l'heure à chaque démarrage de l'application
* sur le poste de gestion.
* retour : la date et l'heure sous la forme d'une chaine de caractères.
**/
void Metier::Unite::horodater(char dateHeure[4]) {
    	time_t tempsCourant = time(0);   
    	struct tm * miseEnForme = localtime( & tempsCourant );
	dateHeure [0]= miseEnForme->tm_mon+1;
	dateHeure [1]= miseEnForme->tm_mday;
	dateHeure [2]= miseEnForme->tm_hour;
	dateHeure [3]= miseEnForme->tm_min;
}

void Metier::Unite::extraireIncidentsA(char aDate[4], list<Incident*> & aIncidentsSalle) {
	char dateHeureIncident[4];
	char dateHeureFinIncident[4];

	if (!incidents.empty())
		for(vector<Incident*>::iterator it=incidents.begin(); it!=incidents.end(); ++it)
		{
			(*it)->getDateHeureIncident(dateHeureIncident);
		
			if ((dateHeureIncident[0] ==aDate[0]) && (dateHeureIncident[1] ==aDate[1]) && (dateHeureIncident[2] ==aDate[2]) && (dateHeureIncident[3] ==aDate[3]) )
				if (!(*it)->isDebutTransmis()) aIncidentsSalle.push_back(*it);

			(*it)->getDateFinIncident(dateHeureIncident);
			if ((dateHeureIncident[0] ==aDate[0]) && (dateHeureIncident[1] ==aDate[1]) && (dateHeureIncident[2] ==aDate[2]) && (dateHeureIncident[3] ==aDate[3]) )
				if (!(*it)->isFinTransmise()) aIncidentsSalle.push_back(*it);
		}
}


void Metier::Unite::associerIncidentDonneeClimat(Metier::Climat* aClimat, list<Incident*> & aIncidentsSalle, Communication::Information &aInformation) {
	char code;
	string dateHeure= "";
	char heureReleve[4];
	char c_dateHeure [4];
	aClimat->getDateHeureReleve(heureReleve);
	/* Initialisation température */
		aInformation.setNatureTemp(Communication::NatureInfo::CL_TEMP);	
		aInformation.setValeurTemp(aClimat->getTemperature()*2);
	/* Initialisation Humidité */
		aInformation.setNatureHumid(Communication::NatureInfo::CL_HUM);
		aInformation.setValeurHumid(aClimat->getHumidity());
	/* Initialisation Gaz */
		aInformation.setNatureGaz(Communication::NatureInfo::CL_QAIR);	
		aInformation.setValeurGaz(aClimat->getGaz()/10);
		aInformation.setSalle(_numero);
		dateHeure=std::to_string((int)heureReleve[0])+'/';
		dateHeure+=std::to_string((int)heureReleve[1])+';';
		dateHeure+=std::to_string((int)heureReleve[2])+'h';
		dateHeure+=std::to_string((int)heureReleve[3])+"mn";
		aInformation.setDate(dateHeure);
	if (!aIncidentsSalle.empty())
		for(list<Incident*>::iterator it=aIncidentsSalle.begin(); it!=aIncidentsSalle.end(); ++it)
		{			
			(*it)->getDateHeureIncident(c_dateHeure);			
			if ((heureReleve[0] ==c_dateHeure[0]) && (heureReleve[1] ==c_dateHeure[1]) && (heureReleve[2] ==c_dateHeure[2]) && (heureReleve[3] ==c_dateHeure[3]) && !(*it)->isDebutTransmis()) 
			{
				/* Traitement début incident température */
				if ((*it)->getTypeIncident().find("Température")!=std::string::npos) 
				{
					code = (*it)->getCode();
				    switch (code)
				    {
					case Communication::NatureInfo::CL_TEMPINCIDENT_MIN :
					    aInformation.setNatureTemp(Communication::NatureInfo::CL_TEMPINCIDENT_MIN);
					    break;
					case Communication::NatureInfo::CL_TEMPINCIDENT_MAX:
					    aInformation.setNatureTemp(Communication::NatureInfo::CL_TEMPINCIDENT_MAX);
					    break;
					case Communication::NatureInfo::CL_TEMP_DEFECTUEUX:
					    aInformation.setNatureTemp(Communication::NatureInfo::CL_TEMP_DEFECTUEUX);
					    break;
					default:
					    break;
				    }

					
				}
				/* Traitement début incident Humidité */
				if ((*it)->getTypeIncident().find("Humidité")!=std::string::npos) 
				{
					code = (*it)->getCode();
				    switch (code)
				    {
					case Communication::NatureInfo::CL_HUMINCIDENT_MIN :
					    aInformation.setNatureHumid(Communication::NatureInfo::CL_HUMINCIDENT_MIN);
					    break;
					case Communication::NatureInfo::CL_HUMINCIDENT_MAX:
					    aInformation.setNatureHumid(Communication::NatureInfo::CL_HUMINCIDENT_MAX);
					    break;
					case Communication::NatureInfo::CL_HUM_DEFECTUEUX:
					    aInformation.setNatureHumid(Communication::NatureInfo::CL_HUM_DEFECTUEUX);
					    break;
					default:
					    break;
				    }
				}

				/* Traitement début incident Gaz */					
				if ((*it)->getTypeIncident().find("Qualité")!=std::string::npos) 
				{
					code = (*it)->getCode();
				    switch (code)
				    {
					case Communication::NatureInfo::CL_QAIRINCIDENT :
					    aInformation.setNatureGaz(Communication::NatureInfo::CL_QAIRINCIDENT);
					    break;
					case Communication::NatureInfo::CL_QAIR_DEFECTUEUX:
					    aInformation.setNatureGaz(Communication::NatureInfo::CL_QAIR_DEFECTUEUX);
					    break;
					default:
					    break;
				    }

					
				}
				(*it)->setDebutTransmis(true);

			}

			(*it)->getDateFinIncident(c_dateHeure);

			if ((heureReleve[0] ==c_dateHeure[0]) && (heureReleve[1] ==c_dateHeure[1]) && (heureReleve[2] ==c_dateHeure[2]) && (heureReleve[3] ==c_dateHeure[3]) && (*it)->getEtat() && !(*it)->isFinTransmise()) 
			{
				/* Traitement fin incident température */
				if ((*it)->getTypeIncident().find("Température")!=std::string::npos) 
				{
					aInformation.setNatureTemp(Communication::NatureInfo::CL_TEMP_FININCIDENT);
					
				}
				/* Traitement fin incident Humidité */
				if ((*it)->getTypeIncident().find("Humidité")!=std::string::npos) 
				{

					aInformation.setNatureHumid(Communication::NatureInfo::CL_HUM_FININCIDENT);
				}

				/* Traitement fin incident Gaz */					
				if ((*it)->getTypeIncident().find("Qualité")!=std::string::npos) 
				{

					aInformation.setNatureGaz(Communication::NatureInfo::CL_QAIR_FININCIDENT);
					
				}
				(*it)->setFinTransmise(true);
			}
		}
}

void Metier::Unite::supprimerreleve(vector<Climat*>::iterator leReleve) {
	climats.erase(leReleve);
}
Metier::Unite::Unite(int nSalle, string adresseCapteur, Communication::C_Capteur * laComCapteur) {
	_numero = nSalle;
	_dateHeureCourante[4]={0};
	consignes=new Consignes();
	Communication::C_Capteur * maComCapteur = new Communication::C_Capteur();
	capteur=new Capteur(adresseCapteur, maComCapteur);
}

vector<Metier::Incident*> Metier::Unite::getIncidents(){
	return incidents;
}

void Metier::Unite::setDateHeureCourante(char dateHeureCourante[4]) {
	for (int i=0; i<4;i++)
	{
		_dateHeureCourante[i]=dateHeureCourante[i];
	}
}



