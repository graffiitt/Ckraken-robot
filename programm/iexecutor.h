#ifndef IEXECUTOR_H
#define IEXECUTOR_H

#include <QObject>
#include "commands/icommand.h"
#include "commandmodel.h"

class IExecutor : public QObject
{
    Q_OBJECT
public:
    IExecutor(CommandModel *model);
    ~IExecutor();

    void setMode(bool step);

    void stop();

public slots:
    void exec();

signals:
    void stopExecCmd();
    void finished();
    void changeLine(int num);

private:
    std::atomic_bool stepMode = false;
    std::atomic_int numCommand = 0; // current line execution
    std::atomic_bool running = false;

    CommandModel *cmdModel;
};

#endif