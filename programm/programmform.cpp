#include "programmform.h"
#include "ui_programmform.h"

ProgrammForm::ProgrammForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProgrammForm)
{
    ui->setupUi(this);
}

ProgrammForm::~ProgrammForm()
{
    delete ui;
}
