#include "ControllerCFG.h"

ControllerCFG::ControllerCFG()
{
	cfgFile = new QFile();
    cfgFile->setFileName(CONTROLLER_CFG_LOCATION);
    cfgFile->open(QIODevice::ReadOnly);
}

std::vector<ControllerLatLng> ControllerCFG::getLatLng()
{
	QTextStream stream(cfgFile);
	QString line;
	ControllerLatLng latLng;
	QStringList list;
	std::vector<ControllerLatLng> controllersLatLng;

	do
	{
		line = stream.readLine();
		//End 
		if(line.trimmed().compare("") == 0)
			continue;

		list = line.split(",", QString::SkipEmptyParts);

		//1 - nome
		//2 - Latitude
		//3 - Longitude
		latLng.name = list.at(0);
		latLng.lat = list.at(1);
		latLng.lng = list.at(2);

		controllersLatLng.push_back(latLng);
	}while(!line.isNull());

	return controllersLatLng;

}
ControllerCFG::~ControllerCFG()
{
	cfgFile->close();

	delete cfgFile;
	cfgFile = nullptr;
}