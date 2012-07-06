#include "DataStreamUtils.h"


QDataStream & operator << (QDataStream &out, const Phase &p)
{
	QString qPhaseDef = p.phaseDef.c_str();

	out << qint32(p.duration) << qint32(p.duration1) << qint32(p.duration2)
		<< qPhaseDef;

    return out;
}

QDataStream & operator >> (QDataStream &in, Phase &p)
{
	qint32 qDuration,qDuration1,qDuration2;
	QString qPhaseDef;

	in >> qDuration >> qDuration1 >> qDuration2 >> qPhaseDef;
	p = Phase(qDuration, qDuration2, qDuration2, qPhaseDef.toStdString());
	return in;
}

QDataStream & operator << (QDataStream &out, const ControllerLogic &l)
{
	QString qSubId = l.subID.c_str();

	QVector<Phase> vector;

	for(int i = 0; i < l.phases->size(); i++)
	{
		vector.push_back(*(l.phases->at(i)));
	}

	out << qSubId << qint32(l.type) << qint32(l.subParameter) << qint32(l.currentPhaseIndex) << vector;

	return out;
}

QDataStream & operator >> (QDataStream &in, ControllerLogic &l)
{
	qint32 type,subParameter,currentPhaseIndex;
	QString qSubId;
	QVector<Phase> vector;
	std::vector<Phase *> *phases = new std::vector<Phase*>();
	Phase *p;
	Phase pActual;

	in >> qSubId >> type >> subParameter >> currentPhaseIndex >> vector;
	
	// MAYBE REMOVE THIS PART
	for(int i = 0; i < vector.size(); i++)
	{
		pActual = vector.at(i);
		p = new Phase();
		p->duration = pActual.duration;
		p->duration1 = pActual.duration1;
		p->duration2 = pActual.duration2;
		p->phaseDef = pActual.phaseDef;
		phases->push_back(p);
	}

	l.currentPhaseIndex = currentPhaseIndex;
	l.phases = phases;
	l.subID = qSubId.toStdString();
	l.type = type;
	l.subParameter = subParameter;

	return in;
}

QDataStream & operator << (QDataStream &out, const StoredControllerLogic &scl)
{
	ControllerLogic *logicClone = scl.getControllerLogic()->clone();
	ControllerLogic l = *logicClone;

	out << l << scl.getStreets() << scl.getUsedIn();

	delete logicClone;
	logicClone = nullptr;

	return out;
}

QDataStream & operator >> (QDataStream &in, StoredControllerLogic &scl)
{
	ControllerLogic logic, *l;
	qint32 totalSize, totalStream;
	QDateTime usedIn;
	QList<Street> streets;

	in >> logic >> streets >> usedIn;

	scl.setStreets(streets);
	scl.setUsedDate(usedIn);
	l = logic.clone();

	scl.setControllerLogic(l);

	return in;
}

QDataStream & operator << (QDataStream &out, const Street &street)
{
	out << qint32(street.queueSize) << qint32(street.carStream);
	return out;
}


QDataStream & operator >> (QDataStream &in, Street &street)
{
	qint32 q, s;
	in >> q >> s;
	street.queueSize = q;
	street.carStream = s;
	return in;
}