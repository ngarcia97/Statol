#include <string>
using namespace std;

#ifndef __TClimat_h__
#define __TClimat_h__

namespace Communication
{
	class TClimat;
}

namespace Communication
{
	class TClimat
	{
		private: string _valeur;
		public: TClimat(string tclimat);
			void setValeur(string adresse);
			string getValeur();
	};
}

#endif
