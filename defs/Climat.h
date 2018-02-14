#include <exception>
using namespace std;

#ifndef __Climat_h__
#define __Climat_h__

// #include "Unité.h"

namespace Metier
{
	class Unite;
	class Climat;
}

namespace Metier
{
	class Climat
	{
		private: float _temperature;
		private: int _humidity;
		private: int _gaz;
		private: char _dateHeureReleve[4];

		public: int ajouterClimat( int aSalle);

		public: void supprimer();

		public: float getTemperature();

		public: int getHumidity();

		public: int getGaz();

		public: void getDateHeureReleve(char dateHeureReleve[4]);

		public : Climat(float temperature, int humidity, int gaz, char dateHeureReleve[4]);
	};
}

#endif
