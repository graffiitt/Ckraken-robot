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
