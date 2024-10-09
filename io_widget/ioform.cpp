#include "ioform.h"
#include "ui_ioform.h"
#include "pherephicalIO.h"

#define QSS_ON "background-color: #00ff00; color:#000000"
#define QSS_OFF "background-color: #ff0000; color:#000000"

IOForm::IOForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::IOForm)
{
    ui->setupUi(this);

    for (int i = 0; i < 8; i++)
    {
        QPushButton *bt = new QPushButton("output " + QString::number(i + 1));
        bt->setStyleSheet(QSS_OFF);
        ui->outputLayout->addWidget(bt);
        btnList.append(bt);
        connect(bt, &QPushButton::clicked, this, &IOForm::on_buttonClicked);
    }
    for (int i = 0; i < 8; i++)
    {
        QPushButton *bt = new QPushButton("input " + QString::number(i + 1));
        bt->setStyleSheet(QSS_OFF);
        ui->inputLayout->addWidget(bt);
        btnList.append(bt);
    }
}

IOForm::~IOForm()
{
    delete ui;
    qDeleteAll(btnList);
}

void IOForm::on_buttonClicked()
{
    QPushButton *bt = static_cast<QPushButton *>(sender());

    bt->setStyleSheet(QSS_ON);
}
