#include <exception>
#include <string>
using namespace std;

#include "../defs/Information.h"
#include "../defs/NatureInfo.h"

char Communication::Information::getValeurTemp() {
	return this->_valeurTemp;
}

void Communication::Information::setValeurTemp(char aValeurTemp) {
	this->_valeurTemp = aValeurTemp;
}

char Communication::Information::getValeurHumid() {
	return this->_valeurHumid;
}

void Communication::Information::setValeurHumid(char aValeurHumid) {
	this->_valeurHumid = aValeurHumid;
}

char Communication::Information::getValeurGaz() {
	return this->_valeurGaz;
}

void Communication::Information::setValeurGaz(char aValeurGaz) {
	this->_valeurGaz = aValeurGaz;
}

Communication::NatureInfo Communication::Information::getNatureTemp() {
	return this->_natureTemp;
}

void Communication::Information::setNatureTemp(Communication::NatureInfo aNatureTemp) {
	this->_natureTemp = aNatureTemp;
}

Communication::NatureInfo Communication::Information::getNatureHumid() {
	return this->_natureHumid;
}

void Communication::Information::setNatureHumid(Communication::NatureInfo aNatureHumid) {
	this->_natureHumid = aNatureHumid;
}

Communication::NatureInfo Communication::Information::getNatureGaz() {
	return this->_natureGaz;
}

void Communication::Information::setNatureGaz(Communication::NatureInfo aNatureGaz) {
	this->_natureGaz = aNatureGaz;
}

void Communication::Information::setSalle(char aSalle) {
	this->_salle = aSalle;
}

char Communication::Information::getSalle() {
	return this->_salle;
}

void Communication::Information::setDate(string aDate) {
	this->_date = aDate;
}

string Communication::Information::getDate() {
	return this->_date;
}

Communication::Information::Information() {
	_valeurTemp = 0;
	_valeurHumid = 0;
	_valeurGaz = 0;
	_natureTemp = CL_TEMP;
	_natureHumid = CL_HUM ;
	_natureGaz = CL_QAIR ;
	_salle = 0;
	_date = "12/31;23h59m";
}

Communication::Information::Information(NatureInfo natureTemp, char valeurTemp, NatureInfo natureHumid, char valeurHumid, NatureInfo natureGaz, char valeurGaz, char salle, string date)
{
	_valeurTemp = valeurTemp;
	_valeurHumid = valeurHumid;
	_valeurGaz = valeurGaz;
	_natureTemp = natureTemp;
	_natureHumid = natureHumid ;
	_natureGaz = natureGaz ;
	_salle = salle;
	_date = date;
}

