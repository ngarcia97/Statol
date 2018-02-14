#include <exception>
#include <vector>


#ifndef __Atelier
#define __Atelier

#include "Unite.h"

namespace Metier
{
	class Unite;
	class Atelier;
}

namespace Metier
{
	class Atelier
	{
		private: long _periodicite;
		public: std::vector<Metier::Unite*> unite;
		public: int verifierClimat();
		public: void verifierIncidents(Unite *unite, char codeIncident[3]);
		public: void transmettreInformations(vector<Metier::Unite*> unite);
		public : char codeIncident[3];
	};
}

#endif
