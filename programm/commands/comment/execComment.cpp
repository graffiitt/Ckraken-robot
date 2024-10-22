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

ICommand::ID_COMMAND ExecutorComment::execCommand(std::atomic_int &number, const QList<ICommand *> &programm)
{
    Q_UNUSED(programm);

    QMetaObject::invokeMethod(StateManager::getInstance(), [this]()
                              { StateManager::getInstance()->setInfo(text); }, Qt::QueuedConnection);

    return ID_COMMAND::COMMENTARY;
}

QJsonObject ExecutorComment::toJSON()
{
    QJsonObject obj;
    obj["index"] = getIndex();
    obj["text"] = text;
    return obj;
}

void ExecutorComment::fromJSON(const QJsonObject &obj)
{
    text = obj["text"].toString();
}
