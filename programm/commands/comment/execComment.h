#ifndef EXECCOMMENT_H
#define EXECCOMMENT_H

#include "../icommand.h"

class ExecutorComment : public ICommand
{

public:
    ExecutorComment(int index);
    ~ExecutorComment();

    QString getStroke();
    void setText(QString data){text = data;};
private:
    QString text;
};

#endif