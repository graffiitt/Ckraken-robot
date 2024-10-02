#ifndef EXECTIMER_H
#define EXECTIMER_H

#include "../icommand.h"

class ExecutorTimer : public ICommand
{
public:
    ExecutorTimer(int index);
    ~ExecutorTimer();

    // virtual
    QString getStroke();
    int execCommand(int number, const QList<ICommand *> &programm);

    void setTime(uint time) { timeDelay = time; };
    uint getTime() { return timeDelay; };

private:
    uint timeDelay = 0;
};

#endif