#include <exception>
#include <list>
#include <vector>


#ifndef __Unite
#define __Unite

#include "../defs/Information.h"

#include "../defs/Incident.h"
#include "../defs/Climat.h"
#include "../defs/C_Informations.h"
#include "../defs/C_Capteur.h"

namespace Communication
{
	class Information;
	class C_Informations;
	class C_Capteur;
}
namespace Metier
{
	class Atelier;
	class Consignes;
	class Capteur;
	class Incident;
	class Climat;
	class Unite;
}

namespace Metier
{
	class Unite
	{
		private: int _numero;
		private: char _dateHeureCourante[4];
		public: Metier::Consignes* consignes;
		public: Metier::Capteur* capteur;
		public: std::vector<Metier::Incident*> incidents;
		public: std::vector<Metier::Climat*> climats;

		public : Unite(int nSalle, string adresseCapteur, Communication::C_Capteur * comCapteur);

		public: int comparerTemperature(float aReleve, float aTempMin, float aTempMAX);

		public: int comparerHumidite(int aReleve, int aHumidMin, int aHumidMAX);

		public: int comparerGaz(int aReleve, int aSeuil);

		public: void ajouterIncident(string type, char  codeIncident);

		/// <summary>
		/// Sont retournés les codes incidents
		/// </summary>
		public: int verifierClimatSalle(int codeIncident [3]);

		public: bool verifierPresenceIncident(string type);

		public: void creerIncident(string type, char  codeIncident);

		public: void finirIncident(string type);

		public: void supprimerIncident(char heureReleve[4]);

		public: void transmettreInformations(Communication::C_Informations *laCommunication);

		public: void horodater(char dateHeure[4]);

		public: void extraireIncidentsA(char* aDate, list<Incident*> & aIncidentsSalle);

		public: void associerIncidentDonneeClimat(Metier::Climat* aClimat, list<Incident*> & aIncidentsSalle, Communication::Information &aInformation);

		public: void supprimerreleve(vector<Climat*>::iterator leReleve);

		public : vector<Metier::Climat*> getClimats();

		public : vector<Metier::Incident*> getIncidents();

		public: void setDateHeureCourante(char aDateHeureCourante[4]);
	};
}


#endif
