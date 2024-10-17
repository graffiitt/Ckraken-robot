#ifndef EXECPRGCHANGE_H
#define EXECPRGCHANGE_H

#include "../icommand.h"

class ExecutorPrgChange : public ICommand
{

public:
    ExecutorPrgChange(int index);
    ~ExecutorPrgChange(){};

    // virtual
    QString getStroke();
    int execCommand(int number, const QList<ICommand *> &programm);

    void setText(QString data) { text = data; };
    QString getText() { return text; };
    QJsonObject toJSON();
    void fromJSON(const QJsonObject &obj);

private:
    QString text;
};

#endif