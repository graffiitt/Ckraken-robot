#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "programmform.h"
#include "settingsform.h"
#include "statemanager.h"

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void on_settingsClicked();
    void on_programmClicked();

private:
    Ui::MainWindow *ui;
    ProgrammForm *programmWidget;
    SettingsForm *settingsWidget;
    //StateManager *stateManager;
};
#endif // MAINWINDOW_H
