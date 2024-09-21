#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
