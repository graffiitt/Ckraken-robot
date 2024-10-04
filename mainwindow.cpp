#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "statemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->upLayout->addWidget(StateManager::getInstance());

    programmWidget = new ProgrammForm(this);
    ui->stackedWidget->addWidget(programmWidget);
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::on_programmClicked);

    settingsWidget = new SettingsForm(this);
    ui->stackedWidget->addWidget(settingsWidget);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::on_settingsClicked);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete programmWidget;
    delete settingsWidget;
}

void MainWindow::on_settingsClicked()
{
    ui->stackedWidget->setCurrentWidget(settingsWidget);
}

void MainWindow::on_programmClicked()
{
    ui->stackedWidget->setCurrentWidget(programmWidget);
}

void MainWindow::on_createFileAction_triggered()
{
    qDebug() << "create file";
    programmWidget->createNewProgramm();
}

void MainWindow::on_openFileAction_triggered()
{
    programmWidget->openProgramm();
}

void MainWindow::on_saveAsFileAction_triggered()
{
    programmWidget->saveAsProgramm();
}

void MainWindow::on_saveAction_triggered()
{
    programmWidget->saveProgramm();
}
