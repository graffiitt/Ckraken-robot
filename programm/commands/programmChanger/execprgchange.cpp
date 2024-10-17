#include "execprgchange.h"
#include <QMetaObject>
#include "statemanager.h"
#include <QDebug>

ExecutorPrgChange::ExecutorPrgChange(int index) : ICommand(index)
{
}

QString ExecutorPrgChange::getStroke()
{

    return "# " + text;
}

int ExecutorPrgChange::execCommand(int number, const QList<ICommand *> &programm)
{
    Q_UNUSED(programm);

    QMetaObject::invokeMethod(StateManager::getInstance(), [this]()
                              { StateManager::getInstance()->setInfo(text); }, Qt::QueuedConnection);

    return number++;
}

QJsonObject ExecutorPrgChange::toJSON()
{
    QJsonObject obj;
    obj["index"] = getIndex();
    obj["text"] = text;
    return obj;
}

void ExecutorPrgChange::fromJSON(const QJsonObject &obj)
{
    text = obj["text"].toString();
}
