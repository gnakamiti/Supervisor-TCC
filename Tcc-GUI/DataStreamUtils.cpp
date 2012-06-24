#include "DataStreamUtils.h"


QDataStream & operator << (QDataStream &out, const Phase &p)
{
	QString qPhaseDef = p.phaseDef.c_str();

	out << quint32(p.duration) << quint32(p.duration1) << quint32(p.duration2)
		<< qPhaseDef;

    return out;
}

QDataStream & operator >> (QDataStream &in, Phase &p)
{
	quint32 qDuration,qDuration1,qDuration2;
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

	out << qSubId << quint32(l.type) << quint32(l.subParameter) << quint32(l.currentPhaseIndex) << vector;

	return out;
}

QDataStream & operator >> (QDataStream &in, ControllerLogic &l)
{
	quint32 type,subParameter,currentPhaseIndex;
	QString qSubId;
	QVector<Phase> vector;
	std::vector<Phase *> *phases = new std::vector<Phase*>();
	Phase *p;
	Phase pActual;
	ControllerLogic *newLogic;

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

	newLogic = new ControllerLogic(qSubId.toStdString(), type, subParameter, currentPhaseIndex, phases);
	l = *newLogic;

	return in;
}

QDataStream & operator << (QDataStream &out, const StoredControllerLogic &scl)
{
	ControllerLogic *logicClone = scl.getControllerLogic()->clone();
	ControllerLogic l = *logicClone;

	out << l << quint32(scl.getTotalQueueSize()) << quint32(scl.getTotalCarStream()) << scl.getUsedIn();

	delete logicClone;
	logicClone = nullptr;

	return out;
}

QDataStream & operator >> (QDataStream &in, StoredControllerLogic &scl)
{
	ControllerLogic logic, *l;
	quint32 totalSize, totalStream;
	QDateTime usedIn;
	StoredControllerLogic *sclPtr = new StoredControllerLogic();
	l = new ControllerLogic();

	in >> logic >> totalSize >> totalStream >> usedIn;

	sclPtr->setTotalCarStream(totalStream);
	sclPtr->setTotalQueueSize(totalSize);
	sclPtr->setUsedDate(usedIn);
	l = logic.clone();

	sclPtr->setControllerLogic(l);
	scl = *sclPtr;

	return in;
}