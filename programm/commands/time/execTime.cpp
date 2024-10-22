#include "execTime.h"
#include "statemanager.h"
#include <QEventLoop>

ExecutorTimer::ExecutorTimer(int index) : ICommand(index)
{
}

ExecutorTimer::~ExecutorTimer()
{
}

QString ExecutorTimer::getStroke()
{
    return "wait " + QString::number(timeDelay);
}

ICommand::ID_COMMAND ExecutorTimer::execCommand(std::atomic_int &number, const QList<ICommand *> &programm)
{
    Q_UNUSED(programm);
    
    QTimer t;
    QEventLoop loop;
    t.connect(this, &ExecutorTimer::stop, &loop, &QEventLoop::quit);
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(timeDelay*1000);
    loop.exec();

    return ID_COMMAND::TIMER;
}

void ExecutorTimer::stopExec()
{
    qDebug() << "stop exec time";
    emit stop();
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
