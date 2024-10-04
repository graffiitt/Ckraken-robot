#include "execTime.h"
#include <QThread>
#include "statemanager.h"

ExecutorTimer::ExecutorTimer(int index) : ICommand(index)
{
}

ExecutorTimer::~ExecutorTimer()
{
}

QString ExecutorTimer::getStroke()
{
    return "delay " + QString::number(timeDelay);
}

int ExecutorTimer::execCommand(int number, const QList<ICommand *> &programm)
{
    Q_UNUSED(programm);
    QThread::sleep(timeDelay);
    return number++;
}

QJsonObject ExecutorTimer::toJSON()
{
    QJsonObject obj;
    obj["index"] = getIndex();
    obj["time"] = QString::number(timeDelay);
    return obj;
}

void ExecutorTimer::fromJSON(const QJsonObject &obj)
{
    timeDelay = obj["time"].toString().toUInt();
}
