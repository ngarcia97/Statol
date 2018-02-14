#include <exception>
#include <string>
using namespace std;

#ifndef __ProtocoleCapteurs_h__
#define __ProtocoleCapteurs_h__
#define TRAMEINEXISTANTE -2
#define OK 1

namespace Communication
{
	class ProtocoleCapteurs;
}

namespace Communication
{
	class ProtocoleCapteurs
	{
		private: string _adresse;
		protected: char _separateur;
		protected: char _fin;
		protected: char _debut;
		protected: string _aBSENCETRAME;

		public: ProtocoleCapteurs();
	};
}

#endif
