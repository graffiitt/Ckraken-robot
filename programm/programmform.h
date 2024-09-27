#ifndef PROGRAMMFORM_H
#define PROGRAMMFORM_H

#include <QWidget>
#include <QDebug>

#include "commentform.h"
#include "commandmodel.h"
#include "iexecutor.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ProgrammForm;
}
QT_END_NAMESPACE

class ProgrammForm : public QWidget
{
    Q_OBJECT

public:
    ProgrammForm(QWidget *parent = nullptr);
    ~ProgrammForm();

signals:
    void changeEditMode(bool);

private:
    Ui::ProgrammForm *ui;
    CommentForm *commentWidget;
    CommandModel *model;
    
    IExecutor *executor;

    void on_stopCommand();
    void on_runCommand();
    void on_createCommand();
    void on_itemClicked(const QModelIndex &index);
};
#endif
