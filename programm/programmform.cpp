#include "programmform.h"
#include "ui_programmform.h"

ProgrammForm::ProgrammForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProgrammForm)
{
    ui->setupUi(this);

    executor = new IExecutor();

    commentWidget = new CommentForm("Commentary");
    ui->commandsWidget->addTab(commentWidget, commentWidget->getName());
    ui->commandsWidget->setCurrentIndex(0);
    connect(this, &ProgrammForm::changeEditMode, commentWidget, &ICommandForm::setEnabled);

    model = new CommandModel();
    ui->tableView->setModel(model);

    connect(ui->holdButton, &QPushButton::clicked, this, &ProgrammForm::on_stopCommand);
    connect(ui->runButton, &QPushButton::clicked, this, &ProgrammForm::on_runCommand);
    connect(ui->createButton, &QPushButton::clicked, this, &ProgrammForm::on_createCommand);
    connect(ui->tableView, &QTableView::clicked, this, &ProgrammForm::on_itemClicked);

    connect(commentWidget, &CommentForm::dataChanged, model, &CommandModel::updateData);
}

ProgrammForm::~ProgrammForm()
{
    delete ui;
    delete executor;
    delete model;
    delete commentWidget;
}

void ProgrammForm::on_stopCommand()
{
    emit changeEditMode(true);
    //ui->tableView->setEnabled(true);

}

void ProgrammForm::on_runCommand()
{
    emit changeEditMode(false);
   // ui->tableView->setEnabled(false);
    executor->exec();
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
        ui->commandsWidget->setCurrentIndex(cmd->getIndex()); // change ui widget for editing
        QWidget *wd = ui->commandsWidget->currentWidget();
        static_cast<ICommandForm *>(wd)->setCommand(cmd);
    }
}
