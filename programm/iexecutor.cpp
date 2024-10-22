#include "iexecutor.h"

#include <QMetaObject>
#include "statemanager.h"

IExecutor::IExecutor(CommandModel *model) : cmdModel(model)
{
}

IExecutor::~IExecutor()
{
    emit stopExecCmd();
}

void IExecutor::setMode(bool step)
{
    StateManager::getInstance()->setIconState(StateManager::STEP, step);
    stepMode = step;
}

void IExecutor::exec()
{
    qDebug() << "start thread";
    running = true;
    QMetaObject::invokeMethod(StateManager::getInstance(), [this]()
                              {
    StateManager::getInstance()->setIconState(StateManager::RUN, true);
    StateManager::getInstance()->setIconState(StateManager::HOLD, false); }, Qt::QueuedConnection);

    const QList<ICommand *> commands = cmdModel->getListCommands();
    for (; (numCommand < cmdModel->getSize()) && (running); numCommand++)
    {
        QMetaObject::invokeMethod(this, "changeLine", Qt::DirectConnection, Q_ARG(int, numCommand));

        //  change programm

        connect(this, &IExecutor::stopExecCmd, cmdModel->getCommand(numCommand), &ICommand::stopExec);
       qDebug()<< cmdModel->getCommand(numCommand)->execCommand(numCommand, commands);
        disconnect(this, &IExecutor::stopExecCmd, 0, 0);

        if (stepMode)
        {
            numCommand++;
            break;
        }
    }
    if (numCommand > cmdModel->getSize() - 1) // end programm
    {
        numCommand = 0;
    }
    QMetaObject::invokeMethod(StateManager::getInstance(), [this]()
                              {
                                StateManager::getInstance()->setIconState(StateManager::RUN, false);
                                emit finished(); }, Qt::QueuedConnection);
    QMetaObject::invokeMethod(this, "changeLine", Qt::DirectConnection, Q_ARG(int, numCommand));
    qDebug() << "stop exec iexecutor";
    return;
}

void IExecutor::stop()
{
    StateManager::getInstance()->setIconState(StateManager::HOLD, true);
    running = false;
    emit stopExecCmd();
}
