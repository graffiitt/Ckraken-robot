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
    ICommand(int indexWidget);
    virtual ~ICommand(){};

    int getIndex();
   
    virtual QString getStroke() = 0;
    virtual int execCommand(int number, const QList<ICommand *> &programm) = 0;
    virtual void stopExec() { qDebug() << "stop exec icommands"; };

    virtual QJsonObject toJSON() = 0;
    virtual void fromJSON(const QJsonObject &obj) = 0;

private:
    int index; // index widget
};

#endif