#ifndef PRGCHANGEFORM_H
#define PRGCHANGEFORM_H

#include <QDebug>
#include "../icommandform.h"
#include "execprgchange.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class PrgChangeForm;
}
QT_END_NAMESPACE

class PrgChangeForm : public ICommandForm
{
    Q_OBJECT

public:
    PrgChangeForm(QString name, QWidget *parent = nullptr);
    ~PrgChangeForm();

    void setCommand(ICommand *cmd);
    ICommand *createCommand(int index);

public slots:
    virtual void setEditing(bool state) { this->setEnabled(state); };

private:
    Ui::PrgChangeForm *ui;
    ExecutorPrgChange *cmd;
};
#endif
