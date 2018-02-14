#include <exception>
#include <string>
#include<string.h>    
#include<sys/socket.h>   
#include<arpa/inet.h> 
#include <unistd.h> 

using namespace std;

#include "../defs/C_Informations.h"
#include "../defs/Information.h"

int Communication::C_Informations::creerSocket(int aPort) {
       
    sock = socket(AF_INET , SOCK_STREAM , 0);
    return sock;
}

bool Communication::C_Informations::seConnecterA(string aAdresseServeur, int aPortServeur) {
	sockaddr_in server;
	creerSocket(aPortServeur);
    	server.sin_addr.s_addr = inet_addr(aAdresseServeur.c_str());
    	server.sin_family = AF_INET;
    	server.sin_port = htons( aPortServeur );
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    	{
            	return false;
    	}
}

int Communication::C_Informations::ecrire(Communication::Information aInformation) {
	char message [13];
	seConnecterA(_adresseGestion, _portTCP);
	tramer( aInformation, message);
        return send(sock , message , strlen(message) , 0);

}

bool Communication::C_Informations::tramer(Communication::Information aInformation, char aInformations[13]) {
	aInformations[0] = T_REQUETE;
	aInformations[1] = CF_TEMP_HUM;
	aInformations[2] = aInformation.getNatureTemp();
	aInformations[3] = aInformation.getValeurTemp();
	aInformations[4] = aInformation.getNatureHumid();
	aInformations[5] = aInformation.getValeurHumid();
	aInformations[6] = aInformation.getNatureGaz();
	aInformations[7] = aInformation.getValeurGaz();
	aInformations[8] = aInformation.getSalle();

	string date = aInformation.getDate();
	string mois = date.substr(0, date.find('/'));
	date = date.erase(0, date.find('/') + 1);
	aInformations[9] = stoi(mois);

	string jour = date.substr(0, date.find(';'));
	date = date.erase(0, date.find(';') + 1);
	aInformations[10] = stoi(jour);

	string heures = date.substr(0, date.find('h'));
	date = date.erase(0, date.find('h') + 1);
	aInformations[11] = stoi(heures);

	string minutes = date.substr(0, date.find('m'));
	aInformations[12] = stoi(minutes);

}

Communication::C_Informations::C_Informations(string adresseGestion, int port) {
	_adresseGestion=adresseGestion;
	_portTCP=port;
}
