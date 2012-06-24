#ifndef _DATA_STREAM_UTILS_H_
#define _DATA_STREAM_UTILS_H_

#include "Controller.h"
#include <QVector>
#include <QDataStream>

class Phase;
class ControllerLogic;
class StoredControllerLogic;

QDataStream & operator << (QDataStream &, const Phase &);
QDataStream & operator >> (QDataStream &, Phase &);

QDataStream & operator << (QDataStream &, const ControllerLogic &);
QDataStream & operator >> (QDataStream &, ControllerLogic &);

QDataStream & operator << (QDataStream &, const StoredControllerLogic &);
QDataStream & operator >> (QDataStream &, StoredControllerLogic &);

#endif