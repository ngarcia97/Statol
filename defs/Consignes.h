#include <exception>
using namespace std;


#ifndef __Consignes_h__
#define __Consignes_h__

namespace Metier
{

	class Consignes;
}

namespace Metier
{
	class Consignes
	{
		private: float _temperatureMin;
		private: float _temperatureMax;
		private: int _humiditeMin;
		private: int _humiditeMax;
		private: int _gaz;


		public: int lireConsignes(int aNumero);

		/// <summary>
		/// retour = 2 => requête humidite inappropriee
		/// </summary>
		public: int getTempHumidGaz(float& aTempMin, float& aTempMAX, int& aHumidMin, int& aHumidMax, int& aGaz);

		public: Consignes();
		public : void setTemperatureMin(float tMin);
	};
}

#endif
