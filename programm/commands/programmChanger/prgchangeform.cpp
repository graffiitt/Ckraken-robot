#include "prgchangeform.h"
#include "ui_prgchangeform.h"

PrgChangeForm::PrgChangeForm(QString name, QWidget *parent)
    : ICommandForm(name, parent), ui(new Ui::PrgChangeForm)
{
    ui->setupUi(this);

    connect(ui->lineEdit, &QLineEdit::textChanged, [&](const QString &str)
            { if(cmd)
            {
                cmd->setText(str);
                emit dataChanged();
            } });
}

PrgChangeForm::~PrgChangeForm()
{
    delete ui;
}

void PrgChangeForm::setCommand(ICommand *cmd)
{
    this->cmd = static_cast<ExecutorPrgChange *>(cmd);
    ui->lineEdit->setText(this->cmd->getText());
}

ICommand *PrgChangeForm::createCommand(int index)
{
    ExecutorPrgChange *cmd = new ExecutorPrgChange(index);
    cmd->setText(ui->lineEdit->text());
    this->cmd = cmd;
    return cmd;
}
