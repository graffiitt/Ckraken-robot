#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QWidget>
#include <QString>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class StateManager;
}
QT_END_NAMESPACE

class StateManager : public QWidget
{
    Q_OBJECT

public:

    enum Icon{
        RUN,
        STEP,
        IO,
        FAULT,
        MCU,
        HOLD
    };

    static StateManager* getInstance()
    {
        static StateManager* inst = new StateManager;
        return inst;
    };
    StateManager(StateManager const &) = delete;
    StateManager &operator=(StateManager const &) = delete;
    ~StateManager();

    void setProgrammName(QString path);
    void setInfo(QString text);
    void setLineNumber(int number);
    void setIconState(enum Icon ico, bool state);

private:
    StateManager(QWidget *parent = nullptr);

    Ui::StateManager *ui;
};
#endif
