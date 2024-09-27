#ifndef IEXECUTOR_H
#define IEXECUTOR_H

#include "commands/icommand.h"
#include <QtConcurrent/qtconcurrentrun.h>

class IExecutor
{
public:
    IExecutor(/* args */);
    ~IExecutor();

    void exec();

private:
    /* data */
};

#endif