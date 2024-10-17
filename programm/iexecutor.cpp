#include "iexecutor.h"
#include <QtConcurrent/qtconcurrentrun.h>
#include <QMetaObject>
#include "statemanager.h"

IExecutor::IExecutor(CommandModel *model) : cmdModel(model)
{
}

IExecutor::~IExecutor()
{
    emit stopExecCmd();
    future.waitForFinished();
}

void IExecutor::setMode(bool step)
{
    StateManager::getInstance()->setIconState(StateManager::STEP, step);
    stepMode = step;
}

void IExecutor::exec()
{
    running = true;
    StateManager::getInstance()->setIconState(StateManager::RUN, true);
    StateManager::getInstance()->setIconState(StateManager::HOLD, false);

    future = QtConcurrent::run([this]()
                               { 
                        const QList<ICommand *> commands = cmdModel->getListCommands();
                        for (; (numCommand < cmdModel->getSize()) && (running); numCommand++)
                        {
                            QMetaObject::invokeMethod(this, "changeLine", Qt::DirectConnection, Q_ARG(int, numCommand));
                            
                            //  change programm

                            connect(this, &IExecutor::stopExecCmd, cmdModel->getCommand(numCommand), &ICommand::stopExec);
                            cmdModel->getCommand(numCommand)->execCommand(numCommand, commands);
                            disconnect(this, &IExecutor::stopExecCmd,0, 0);

                            if(stepMode)
                            {
                                numCommand++;
                                break;
                            }
                        }
                        if(numCommand > cmdModel->getSize()-1) numCommand =0;
                        QMetaObject::invokeMethod(StateManager::getInstance(), [this]()
                              {
                                 StateManager::getInstance()->setIconState(StateManager::RUN, false);
                                 emit finished();
                              }, Qt::QueuedConnection); });
}

void IExecutor::stop()
{
    StateManager::getInstance()->setIconState(StateManager::HOLD, true);
    running = false;
    emit stopExecCmd();
}
