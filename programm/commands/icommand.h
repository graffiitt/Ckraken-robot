#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QString>

class ICommand
{
private:
    /* data */
public:
    ICommand(int indexWidget);
    ~ICommand();

    int getIndex();
    virtual QString getStroke() = 0;

private:
    int index; // index widget
};

#endif