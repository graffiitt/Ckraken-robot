#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QDebug>

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QList>

class ICommand : public QObject
{
public:
    enum ID_COMMAND
    {
        CHANGE_PRG,
        TIMER,
        COMMENTARY,
    };

    ICommand(int indexWidget){};
    virtual ~ICommand() {};

    int getIndex() { return index; };

    virtual QString getStroke() = 0;
    virtual ID_COMMAND execCommand(std::atomic_int &number, const QList<ICommand *> &programm) = 0;
    virtual void stopExec() { qDebug() << "stop exec icommands"; };

    virtual QJsonObject toJSON() = 0;
    virtual void fromJSON(const QJsonObject &obj) = 0;

private:
    int index; // index widget
};

#endif