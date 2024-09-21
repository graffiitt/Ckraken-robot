#ifndef PROGRAMMFORM_H
#define PROGRAMMFORM_H

#include <QWidget>
#include <QDebug>

#include "commentform.h"
#include "commandmodel.h"

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

private:
    Ui::ProgrammForm *ui;
    CommentForm *commentWidget;
    CommandModel *model;
    
    void on_createCommand();
    void on_itemClicked(const QModelIndex &index);
};
#endif
