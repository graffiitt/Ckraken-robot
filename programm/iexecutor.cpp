#include "iexecutor.h"
#include <QtConcurrent/qtconcurrentrun.h>
#include <QMetaObject>
#include "statemanager.h"

IExecutor::IExecutor(CommandModel *model) : cmdModel(model)
{
}

IExecutor::~IExecutor()
{
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

    QtConcurrent::run([this]()
                      { 
                        const QList<ICommand *> commands = cmdModel->getListCommands();
                        for (; (numCommand < cmdModel->getSize()) && (running); numCommand++)
                        {
                            QMetaObject::invokeMethod(this, "changeLine", Qt::QueuedConnection, Q_ARG(int, numCommand));
                          
                            // QThread::sleep(1);
                            cmdModel->getCommand(numCommand)->execCommand(numCommand, commands);
                            
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
                              }, Qt::QueuedConnection);            
                        finished(); });
}

void IExecutor::stop()
{
    StateManager::getInstance()->setIconState(StateManager::HOLD, true);
    running = false;
}
