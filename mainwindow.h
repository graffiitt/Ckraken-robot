#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "programmform.h"
#include "settingsform.h"
#include "ioform.h"

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

private slots:
    void on_settingsClicked();
    void on_programmClicked();
    void on_createFileAction_triggered();
    void on_openFileAction_triggered();
    void on_saveAsFileAction_triggered();
    void on_saveAction_triggered();

private:
    Ui::MainWindow *ui;
    ProgrammForm *programmWidget;
    SettingsForm *settingsWidget;
    IOForm *ioWidget;
};
#endif // MAINWINDOW_H
