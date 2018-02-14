#include <exception>
#include <vector>
#include <iostream>


#include "../defs/Atelier.h"
#include "../defs/Unite.h"
#include "../defs/Incident.h"

using namespace std;

/*
int Metier::Atelier::verifierClimat() {
	int codeIncident [3];
	int error;
	for (int i=0;i<unites.size();i++)
	{
		error = unites[i]->verifierClimatSalle(codeIncident);
		verifierIncidents(unites[i],codeIncident);
		transmettreInformations;
		switch (codeIncident[0])
		{
			case CL_TEMPINCIDENT_MIN :
				cout <<"Temp�rature trop faible" << endl;
				break;
			case CL_TEMPINCIDENT_MAX :
				cout <<"Temp�rature trop �lev�e" << endl;
				break;
			case CL_TEMP_DEFECTUEUX :
				cout <<"Capteur de temp�rature d�fectueux" << endl;
				break;
			case CL_TEMP_FININCIDENT :
				cout <<"Fin d'incident temp�rature" << endl;
				break;
			default :
				break;
		}
		switch (codeIncident[1])
		{
default :
break;
		}
	}
}*/

void Metier::Atelier::verifierIncidents(Unite *unite, char codeIncident[3]) {
		
		if (codeIncident[0]=1) {
			unite -> finirIncident();
		} 
		else switch (codeIncident[0]) {
			case 2 :  
				unite->ajouterIncident("CL_TEMPINCIDENT_MIN", codeIncident);
				break;
			case 3 :  
				unite->ajouterIncident("CL_TEMPINCIDENT_MAX", codeIncident);
				break;
			case 4 :  
				unite->ajouterIncident("CL_TEMP_DEFECTUEUX", codeIncident);
				break;
		 }


		if (codeIncident[1]=1) {
			unite -> finirIncident();
		}  
		else switch (codeIncident[1]) {
			case 2 :  

				unite->ajouterIncident("CL_HUMINCIDENT_MIN", codeIncident);
				break;
			case 3 :  
				unite->ajouterIncident("CL_HUMINCIDENT_MAX", codeIncident);
				break;
			case 4 :  
				unite->ajouterIncident("CL_HUM_DEFECTUEUX", codeIncident);
				break;
			case 5 :  
				unite->ajouterIncident("CL_HUMNONINSTAL", codeIncident);
				break;
		 }


		if (codeIncident[2]=1) {
			unite -> finirIncident();
		}
		else switch (codeIncident[2]) {
			case 2 :  
				unite->ajouterIncident("CL_QAIRINCIDENT", codeIncident);
				break;
			case 3 :  
				unite->ajouterIncident("CL_QAIR_DEFECTUEUX", codeIncident);
				break;
			case 5 :  
				unite->ajouterIncident("CL_QAIRNONINSTAL", codeIncident);
				break;
		 }
			
}

void Metier::Atelier::transmettreInformations(vector<Metier::Unite*> unite) {
	
	for(vector<Unite*>::iterator it=unite.begin(); it!=unite.end(); ++it) {
		Metier::Unite::transmettreInformations(Communication::C_Informations *laCommunication);
	}
}

