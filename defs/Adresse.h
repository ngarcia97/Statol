#include <exception>
#include <string>
using namespace std;

#ifndef __Adresse_h__
#define __Adresse_h__

namespace Communication
{
	class Adresse;
}

namespace Communication
{
	class Adresse
	{
		private: string _valeur;

		public: Adresse(string adresse);
			void setValeur(string adresse);
			string getValeur();
	};
}

#endif
