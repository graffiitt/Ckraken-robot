#include "statemanager.h"
#include "ui_statemanager.h"

StateManager::StateManager(QWidget *parent)
    : QWidget(parent), ui(new Ui::StateManager)
{
    ui->setupUi(this);
}

StateManager::~StateManager()
{
    delete ui;
}

void StateManager::setInfo(QString text)
{
    ui->infoLabel->setText(text);
}
