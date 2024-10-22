#ifndef EXECPRGCHANGE_H
#define EXECPRGCHANGE_H

#include "../icommand.h"

class ExecutorPrgChange : public ICommand
{

public:
    ExecutorPrgChange(int index);
    ~ExecutorPrgChange() {};

    // virtual
    QString getStroke();
    ID_COMMAND execCommand(std::atomic_int &number, const QList<ICommand *> &programm);
    QJsonObject toJSON();
    void fromJSON(const QJsonObject &obj);

private:
};

#endif