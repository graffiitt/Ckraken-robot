#ifndef IOFORM_H
#define IOFORM_H

#include <QWidget>
#include <QList>
#include <QPushButton>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class IOForm;
}
QT_END_NAMESPACE

class IOForm : public QWidget
{
    Q_OBJECT
public:
    IOForm(QWidget *parent = nullptr);
    ~IOForm();

private:
    Ui::IOForm *ui;
    QList<QPushButton *> btnList;

    void on_buttonClicked();
};
#endif
