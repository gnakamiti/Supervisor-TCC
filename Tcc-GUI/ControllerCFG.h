#ifndef _CONTROLLER_CFG_
#define _CONTROLLER_CFG_

#include <QFile>
#include <QTextStream>
#include <vector>
#include <QStringList>
//#include <QIODevice>
#include "constants.h"

//Read the CFG file with the controller names and position to put in the map web view
//Conversions String to number are made via javascript
typedef struct LatLongStruct
{
	QString name;
	QString lat;
	QString lng;
} ControllerLatLng;

class ControllerCFG
{
private:
	QFile *cfgFile;

public:
	ControllerCFG();
	~ControllerCFG();

	std::vector<ControllerLatLng>  getLatLng();
};


#endif