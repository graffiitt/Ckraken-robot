#include "execComment.h"

ExecutorComment::ExecutorComment(int index) : ICommand(index)
{
}

ExecutorComment::~ExecutorComment()
{
}

QString ExecutorComment::getStroke()
{
    return "#" + text;
}
