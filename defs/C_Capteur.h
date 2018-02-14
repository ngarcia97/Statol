#include <exception>
#include <string>
#include <map>
#include <thread>
using namespace std;

#ifndef __C_Capteur_h__
#define __C_Capteur_h__


//#include "../defs/serialib.h"
#include "../defs/ProtocoleCapteurs.h"
#include "../defs/Adresse.h"
#include "../defs/TClimat.h"

#define         UART2_RXD             "/dev/ttyO2" 

namespace Communication
{
	//class serialib;
	// class ProtocoleCapteurs;
	class C_Capteur;
}

namespace Communication
{
	class C_Capteur: public Communication::ProtocoleCapteurs
	{
		private: string _port;
		private: map<string, string> _salve;
		//public: Communication::serialib* SL;

		public: void lire(string &trame);

		public: int ajouterTrameASalve(string trame) ;

		public: thread activerReception();

		public: int extraireTrame(string aAdresse, string& aTrame);

		public: int remettreAZeroLaSalve();

		public: C_Capteur();
		public : map<string, string>  getSalve();
	};
}

#endif
