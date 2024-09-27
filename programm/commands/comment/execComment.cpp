#include "execComment.h"
#include <QMetaObject>
#include "statemanager.h"
#include <QDebug>

ExecutorComment::ExecutorComment(int index) : ICommand(index)
{
}

ExecutorComment::~ExecutorComment()
{
}

QString ExecutorComment::getStroke()
{

    return "# " + text;
}

int ExecutorComment::execCommand(int number, const QList<ICommand *> *programm)
{
    Q_UNUSED(programm);

    QMetaObject::invokeMethod(this, []()
                              { 
                                
                                qDebug() << "comment exec invoke"; }, Qt::QueuedConnection);

    return number++;
}
