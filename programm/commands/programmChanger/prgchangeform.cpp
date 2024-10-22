#include "prgchangeform.h"
#include "ui_prgchangeform.h"

PrgChangeForm::PrgChangeForm(QString name, QWidget *parent)
    : ICommandForm(name, parent), ui(new Ui::PrgChangeForm)
{
    ui->setupUi(this);
}

PrgChangeForm::~PrgChangeForm()
{
    delete ui;
}

void PrgChangeForm::setCommand(ICommand *cmd)
{
    this->cmd = static_cast<ExecutorPrgChange *>(cmd);
   
}

ICommand *PrgChangeForm::createCommand(int index)
{
    ExecutorPrgChange *cmd = new ExecutorPrgChange(index);
    
    
    return cmd;
}
