#include "programmform.h"
#include "ui_programmform.h"
#include "statemanager.h"

ProgrammForm::ProgrammForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProgrammForm)
{
    ui->setupUi(this);

    commentWidget = new CommentForm("Commentary");
    ui->commandsWidget->addTab(commentWidget, commentWidget->getName());
    connect(this, &ProgrammForm::changeEditMode, commentWidget, &ICommandForm::setEnabled);

    timeWidget = new TimeForm("Time");
    ui->commandsWidget->addTab(timeWidget, timeWidget->getName());
    connect(this, &ProgrammForm::changeEditMode, timeWidget, &ICommandForm::setEnabled);

    model = new CommandModel();
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->tableView->setWordWrap(true);
    executor = new IExecutor(model);

    ui->commandsWidget->setCurrentIndex(0);

    connect(executor, &IExecutor::finished, [this]()
            {
                emit changeEditMode(true); 
                ui->runButton->setEnabled(true); });
    connect(executor, &IExecutor::changeLine, this, &ProgrammForm::on_changeLine, Qt::DirectConnection);

    connect(ui->holdButton, &QPushButton::clicked, this, &ProgrammForm::on_stopCommand);
    connect(ui->runButton, &QPushButton::clicked, this, &ProgrammForm::on_runCommand);
    connect(ui->stepButton, &QPushButton::toggled, [this](bool state)
            { executor->setMode(state); });
    connect(ui->createButton, &QPushButton::clicked, this, &ProgrammForm::on_createCommand);
    connect(ui->deleteButton, &QPushButton::clicked, this, &ProgrammForm::on_deleteCommand);
    connect(ui->tableView, &QTableView::clicked, this, &ProgrammForm::on_itemClicked);

    connect(commentWidget, &CommentForm::dataChanged, model, &CommandModel::updateData);
    connect(timeWidget, &CommentForm::dataChanged, model, &CommandModel::updateData);
}

ProgrammForm::~ProgrammForm()
{
    executor->stop();
    delete ui;
    delete executor;
    delete model;
    delete commentWidget;
    delete timeWidget;
}

void ProgrammForm::on_stopCommand()
{
    executor->stop();
}

void ProgrammForm::on_runCommand()
{
    emit changeEditMode(false);
    ui->runButton->setEnabled(false);
    executor->exec();
}

void ProgrammForm::on_createCommand()
{
    QWidget *wd = ui->commandsWidget->currentWidget();
    model->insertCommand(ui->tableView->currentIndex(),
                         static_cast<ICommandForm *>(wd)->createCommand(ui->commandsWidget->currentIndex()));
}

void ProgrammForm::on_deleteCommand()
{
    model->deleteCommand(ui->tableView->currentIndex());
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

void ProgrammForm::on_changeLine(int num)
{
    StateManager::getInstance()->setLineNumber(num);
    ui->tableView->setCurrentIndex(model->index(num, 0));
}