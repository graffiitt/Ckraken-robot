#ifndef EXECTIMER_H
#define EXECTIMER_H

#include "../icommand.h"
#include <QTimer>

class ExecutorTimer : public ICommand
{
    Q_OBJECT
public:
    ExecutorTimer(int index);
    ~ExecutorTimer();

    // virtual
    QString getStroke() override;
    int execCommand(int number, const QList<ICommand *> &programm) override;
    virtual void stopExec() override;
    QJsonObject toJSON() override;
    void fromJSON(const QJsonObject &obj) override;

    void setTime(uint time) { timeDelay = time; };
    uint getTime() { return timeDelay; };

signals:
    void stop();

private:
    uint timeDelay = 0;
};

#endif