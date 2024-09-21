#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QWidget>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SettingsForm;
}
QT_END_NAMESPACE

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();

private:
    Ui::SettingsForm *ui;
};
#endif
