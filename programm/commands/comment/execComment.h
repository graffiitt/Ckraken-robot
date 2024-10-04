#ifndef EXECCOMMENT_H
#define EXECCOMMENT_H

#include "../icommand.h"

class ExecutorComment : public ICommand
{

public:
    ExecutorComment(int index);
    ~ExecutorComment();

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