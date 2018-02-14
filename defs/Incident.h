#include <exception>
#include <string>
#include "../defs/NatureInfo.h"
using namespace std;

#ifndef __Incident
#define __Incident


namespace Metier
{
	class Incident;
}


namespace Metier
{
	class Incident
	{
		private: string _type;
		private: char _dateHeureIncident[4];
		private: char _dateFinIncident[4];
		private: char _code;
		
		/*etat = false : en cours;
		* etat = true : fini;       */
		private: bool etat;
		private: bool _debutTransmis;

		private: bool _finTransmise;

		public: string getTypeIncident();

		public: char getCode();

		public: void setTypeDate(string type, char aDate[4]);

		public: void finir(char aDate[4]);

		public: void setNonTransmis();

		public: void supprimer();

		public: void setDebutTransmis(bool aDebutTransmis);

		public: bool isDebutTransmis();

		public: void setFinTransmise(bool aFinTransmise);

		public: bool isFinTransmise();

		public: bool getEtat();

		public : void getDateHeureIncident(char dateHeureIncident[4]);

		public: void getDateFinIncident(char dateHeureFinIncident[4]);

		public : Incident(string type, char dateHeureIncident [4],char  codeIncident);
	};
}

#endif
