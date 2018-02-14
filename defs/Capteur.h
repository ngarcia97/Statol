#include <exception>
#include <string>
using namespace std;

#ifndef __Capteur_h__
#define __Capteur_h__

#include "C_Capteur.h"
#include "../defs/ProtocoleCapteurs.h"

namespace Metier
{
	class Unite;
	class Capteur;
}

namespace Metier
{
	class Capteur : public Communication::ProtocoleCapteurs
	{
		private: string _adresse;
			Communication::C_Capteur *leCapteur;

		/// <summary>
		/// retour = 2 => requête humidite inappropriee
		/// </summary>
		public: int getTempHumid(float& aTemperature, int& aHumidity);

		/// <summary>
		/// retour = 0 => requête gaz inappropriee
		/// </summary>
		public: int getGaz(int& aValeur);

		public: int lireClimat(char aAdresse[5]);

		/// <summary>
		/// Methode permettant de supprimer la trame traitee de la collection de trames capteurs qui arrivent de façon asynchrone.
		/// Scenario :
		/// Un capteur est defectueux (Son module Zigbee ne transmet plus). Il ne faut pas qu'une ancienne trame laisse penser que la transmission est toujours presente.)
		/// </summary>
		public: void supprimerEnregistrement();
		public : Capteur(string _adresse,Communication::C_Capteur *unCapteur);
	};
}

#endif
