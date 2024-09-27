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
    StateManager(QWidget *parent = nullptr);
    ~StateManager();

    void setInfo(QString text);

private:
    Ui::StateManager *ui;
};
#endif
