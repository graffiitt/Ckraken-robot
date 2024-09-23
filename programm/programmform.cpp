#include "programmform.h"
#include "ui_programmform.h"

ProgrammForm::ProgrammForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProgrammForm)
{
    ui->setupUi(this);

    commentWidget = new CommentForm("Commentary");
    ui->commandsWidget->addTab(commentWidget, commentWidget->getName());
    ui->commandsWidget->setCurrentIndex(0);

    model = new CommandModel();
    ui->tableView->setModel(model);

    connect(ui->createButton, &QPushButton::clicked, this, &ProgrammForm::on_createCommand);
    connect(ui->tableView, &QTableView::clicked, this, &ProgrammForm::on_itemClicked);
    
    connect(commentWidget, &CommentForm::dataChanged, model, &CommandModel::updateData);
}

ProgrammForm::~ProgrammForm()
{
    delete ui;
    delete model;
    delete commentWidget;
}

void ProgrammForm::on_createCommand()
{
    QWidget *wd = ui->commandsWidget->currentWidget();
    model->insertCommand(ui->tableView->currentIndex(),
                         static_cast<ICommandForm *>(wd)->createCommand(ui->commandsWidget->currentIndex()));
}

void ProgrammForm::on_itemClicked(const QModelIndex &index)
{
    ICommand *cmd = model->getCommand(index);
    if (cmd)
    {
        ui->commandsWidget->setCurrentIndex(cmd->getIndex());
        QWidget *wd = ui->commandsWidget->currentWidget();
        static_cast<ICommandForm *>(wd)->setCommand(cmd);
    }
}
