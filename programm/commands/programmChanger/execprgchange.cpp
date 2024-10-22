#include "execprgchange.h"
#include <QMetaObject>
#include "statemanager.h"
#include <QDebug>

ExecutorPrgChange::ExecutorPrgChange(int index) : ICommand(index)
{
}

QString ExecutorPrgChange::getStroke()
{

    return QString();
}

ICommand::ID_COMMAND ExecutorPrgChange::execCommand(std::atomic_int &number, const QList<ICommand *> &programm)
{
    Q_UNUSED(programm);

    return ID_COMMAND::CHANGE_PRG;
}

QJsonObject ExecutorPrgChange::toJSON()
{
    QJsonObject obj;
    obj["index"] = getIndex();

    return obj;
}

void ExecutorPrgChange::fromJSON(const QJsonObject &obj)
{
}
