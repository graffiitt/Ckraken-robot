#include "commentform.h"
#include "ui_commentform.h"

CommentForm::CommentForm(QString name, QWidget *parent)
    : ICommandForm(name, parent), ui(new Ui::CommentForm)
{
    ui->setupUi(this);

    connect(ui->lineEdit, &QLineEdit::textChanged, [&](const QString &str)
            { if(cmd)
            {
                cmd->setText(str);
                emit dataChanged();
            } });
}

CommentForm::~CommentForm()
{
    delete ui;
}

void CommentForm::setCommand(ICommand *cmd)
{
    this->cmd = static_cast<ExecutorComment *>(cmd);
    ui->lineEdit->setText(this->cmd->getText());
}

ICommand *CommentForm::createCommand(int index)
{
    ExecutorComment *cmd = new ExecutorComment(index);
    cmd->setText(ui->lineEdit->text());
    this->cmd = cmd;
    return cmd;
}
