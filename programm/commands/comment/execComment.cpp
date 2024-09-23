#include "execComment.h"

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
    return number ++;
}
