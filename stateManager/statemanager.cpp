#include "statemanager.h"
#include "ui_statemanager.h"

#define redColor "background-color: #ff0000; color:#000000"
#define greenColor "background-color: #00ff00; color:#000000"
#define yellowColor "background-color: #ffff00; color:#000000"
#define emptyColor ""

StateManager::StateManager(QWidget *parent)
    : QWidget(parent), ui(new Ui::StateManager)
{
    ui->setupUi(this);
}

StateManager::~StateManager()
{
    delete ui;
}

void StateManager::setProgrammName(QString path)
{
    ui->prgNameLabel->setText(path.split('/').takeLast());
}

void StateManager::setInfo(QString text)
{
    ui->infoLabel->setText(text);
}

void StateManager::setLineNumber(int number)
{
    ui->lineNumLabel->setText("line " + QString::number(number+1));
}

void StateManager::setIconState(Icon ico, bool state)
{
    switch (ico)
    {
    case Icon::RUN:
        state ? ui->runLabel->setStyleSheet(greenColor) : ui->runLabel->setStyleSheet(emptyColor);
        break;
    case Icon::STEP:
        state ? ui->stepLabel->setStyleSheet(yellowColor) : ui->stepLabel->setStyleSheet(emptyColor);
        break;
    case Icon::HOLD:
        state ? ui->holdLabel->setStyleSheet(redColor) : ui->holdLabel->setStyleSheet(emptyColor);
        break;
    case Icon::FAULT:
        state ? ui->faultLabel->setStyleSheet(redColor) : ui->faultLabel->setStyleSheet(emptyColor);
        break;

    case Icon::MCU:
        state ? ui->mcuLabel->setStyleSheet(yellowColor) : ui->mcuLabel->setStyleSheet(emptyColor);
        break;
    default:
        break;
    }
}
