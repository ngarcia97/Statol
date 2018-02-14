#include <exception>
#include <string>
using namespace std;

#ifndef __C_Informations_h__
#define __C_Informations_h__

#include "../defs/Information.h"

#define T_REQUETE 0x01
#define T_REPONSE 0x02
#define CF_TEMP_HUM 0x04

namespace Communication
{
	class Information;
	class C_Informations;
}

namespace Communication
{
	class C_Informations
	{
		private: string _adresseGestion;
		private: int _portTCP;
		private :  int sock;

		/// <summary>
		/// socket + bind
		/// </summary>
		private: int creerSocket(int aPort);

		public: bool seConnecterA(string aAdresseServeur, int aPortServeur);

		public: int ecrire(Communication::Information aInformation);

		public: bool tramer(Communication::Information aInformation, char aInformations[13]);

		public: C_Informations(string adresseGestion, int port);
	};
}

#endif
