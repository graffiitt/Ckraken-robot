#include "timeform.h"
#include "ui_timeForm.h"

TimeForm::TimeForm(QString name, QWidget *parent)
    : ICommandForm(name, parent), ui(new Ui::TimeForm)
{
    ui->setupUi(this);

    connect(ui->timeBox, &QSpinBox::textChanged, [&](const QString &str)
            { 
            if(cmd)
            {
                cmd->setTime(str.toUInt());
                emit dataChanged();
            } });
}

TimeForm::~TimeForm()
{
    delete ui;
}

void TimeForm::setCommand(ICommand *cmd)
{
    this->cmd = static_cast<ExecutorTimer *>(cmd);
    ui->timeBox->setValue(this->cmd->getTime());
}

ICommand *TimeForm::createCommand(int index)
{
    ExecutorTimer *cmd = new ExecutorTimer(index);
    cmd->setTime(ui->timeBox->value());
    this->cmd = cmd;
    return cmd;
}
