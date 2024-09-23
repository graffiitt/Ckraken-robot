#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QString>
#include <QList>

class ICommand
{
private:
    /* data */
public:
    ICommand(int indexWidget);
    ~ICommand();

    virtual QString getStroke() = 0;
    virtual int execCommand(int number, const QList<ICommand*> *programm) = 0;
    int getIndex();

private:
    int index; // index widget
};

#endif