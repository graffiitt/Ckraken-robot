#ifndef TIMEFORM_H
#define TIMEFORM_H

#include <QDebug>
#include "../icommandform.h"
#include "execTime.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class TimeForm;
}
QT_END_NAMESPACE

class TimeForm : public ICommandForm
{
    Q_OBJECT

public:
    TimeForm(QString name, QWidget *parent = nullptr);
    ~TimeForm();

    void setCommand(ICommand *cmd);
    ICommand *createCommand(int index);

private:
    Ui::TimeForm *ui;
    ExecutorTimer *cmd;
};
#endif
