#ifndef COMMENTFORM_H
#define COMMENTFORM_H

#include <QDebug>
#include "../icommandform.h"
#include "execComment.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class CommentForm;
}
QT_END_NAMESPACE

class CommentForm : public ICommandForm
{
    Q_OBJECT

public:
    CommentForm(QString name, QWidget *parent = nullptr);
    ~CommentForm();

    void setCommand(ICommand *cmd);
    ICommand *createCommand(int index);

public slots:
    virtual void setEditing(bool state) { this->setEnabled(state); };

private:
    Ui::CommentForm *ui;
    ExecutorComment *cmd;
};
#endif
