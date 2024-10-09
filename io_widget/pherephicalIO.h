#ifndef PHREI_IO_H
#define PHREI_IO_H

#include <QTimer>
#include <QObject>
#include <QDebug>

class PherephicalIO : public QObject
{
    Q_OBJECT
public:
    PherephicalIO(PherephicalIO const &) = delete;
    PherephicalIO &operator=(PherephicalIO const &) = delete;
    ~PherephicalIO()
    {
        delete timer;
    };
    static PherephicalIO *getInstance()
    {
        static PherephicalIO *inst = new PherephicalIO();
        return inst;
    };

    void startRequesting(bool state)
    {
        if (state)
            timer->start();
        else
            timer->stop();
    };

private:
    QTimer *timer;

    PherephicalIO()
    {
        timer = new QTimer(this);
        timer->setInterval(1000);
        QObject::connect(timer, &QTimer::timeout, this, &PherephicalIO::on_timer_timeout);
    };

    void on_timer_timeout()
    {
        qDebug() << "request inputs";
    };
};

#endif