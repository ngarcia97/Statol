#include <exception>
#include <string>
using namespace std;

#ifndef __Information_h__
#define __Information_h__

#include "NatureInfo.h"

namespace Communication
{
	// enum NatureInfo;
	class Information;
}

namespace Communication
{
	class Information
	{
		private: unsigned char _valeurTemp;
		private: unsigned char _valeurHumid;
		private: unsigned char _valeurGaz;
		private: Communication::NatureInfo _natureTemp;
		private: Communication::NatureInfo _natureHumid;
		private: Communication::NatureInfo _natureGaz;
		private: char _salle;
		private: string _date;

		public: char getValeurTemp();

		public: void setValeurTemp(char aValeurTemp);

		public: char getValeurHumid();

		public: void setValeurHumid(char aValeurHumid);

		public: char getValeurGaz();

		public: void setValeurGaz(char aValeurGaz);

		public: Communication::NatureInfo getNatureTemp();

		public: void setNatureTemp(Communication::NatureInfo aNatureTemp);

		public: Communication::NatureInfo getNatureHumid();

		public: void setNatureHumid(Communication::NatureInfo aNatureHumid);

		public: Communication::NatureInfo getNatureGaz();

		public: void setNatureGaz(Communication::NatureInfo aNatureGaz);

		public: void setSalle(char aSalle);

		public: char getSalle();

		public: void setDate(string aDate);

		public: string getDate();

		public: Information();

		public: Information(NatureInfo natureTemp, char valeurTemp, NatureInfo natureHumid, char valeurHumid, NatureInfo natureGaz, char valeurGaz, char salle, string date);
	};
}

#endif
