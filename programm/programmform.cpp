#include "programmform.h"
#include "ui_programmform.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QFileDialog>
#include <QDir>
#include <QFile>

#include "statemanager.h"

ProgrammForm::ProgrammForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProgrammForm)
{
    ui->setupUi(this);

    // check folder
    QDir dir(pathFolder);
    if (dir.isEmpty())
        dir.mkpath(pathFolder);

    commentWidget = new CommentForm("Commentary");
    ui->commandsWidget->addTab(commentWidget, commentWidget->getName());
    connect(this, &ProgrammForm::changeEditMode, commentWidget, &ICommandForm::setEnabled);

    timeWidget = new TimeForm("Time");
    ui->commandsWidget->addTab(timeWidget, timeWidget->getName());
    connect(this, &ProgrammForm::changeEditMode, timeWidget, &ICommandForm::setEnabled);

    prgChanger = new PrgChangeForm("prg loader");
    ui->commandsWidget->addTab(prgChanger, prgChanger->getName());
    connect(this, &ProgrammForm::changeEditMode, prgChanger, &ICommandForm::setEnabled);

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
    connect(timeWidget, &TimeForm::dataChanged, model, &CommandModel::updateData);
    connect(prgChanger, &PrgChangeForm::dataChanged, model, &CommandModel::updateData);
}

ProgrammForm::~ProgrammForm()
{
    executor->stop();
    delete ui;
    delete executor;
    delete model;
    delete commentWidget;
    delete timeWidget;
    delete prgChanger;
}

void ProgrammForm::openProgramm()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                "open programm",
                                                pathFolder, "*.json ;; *.prg");
    if (path.isEmpty())
        return;

    model->deleteAllCommands();
    pathProgramm = path;
    loadFile(pathProgramm);
}

void ProgrammForm::saveProgramm()
{
    if (pathProgramm.isEmpty())
    {
        saveAsProgramm();
    }
    writeFile(pathProgramm);
}

void ProgrammForm::saveAsProgramm()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                "save as programm",
                                                pathFolder,
                                                "*.json ;; *.prg");
    if (path.isEmpty())
        return;
    pathProgramm = path;
    writeFile(pathProgramm);
    qDebug() << "path:" << path;
}

void ProgrammForm::createNewProgramm()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                "save as programm",
                                                pathFolder,
                                                "*.json ;; *.prg");
    if (path.isEmpty())
        return;
    model->deleteAllCommands();
    pathProgramm = path;
    writeFile(pathProgramm);
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

void ProgrammForm::writeFile(QString path)
{
    QFile saveFile(path);
    if (saveFile.open(QIODevice::WriteOnly)) // на чтение
    {
        QJsonObject js_obj;
        js_obj["parser_version"] = 1;

        QList<ICommand *> cmd = model->getListCommands();
        QJsonArray arry;
        for (QList<ICommand *>::iterator it = cmd.begin(); it != cmd.end(); it++)
        {
            arry.append((*it)->toJSON());
        }

        js_obj["items"] = arry;
        saveFile.write(QJsonDocument(js_obj).toJson());
        saveFile.close();
    }
    else
    {
        StateManager::getInstance()->setIconState(StateManager::Icon::FAULT, true);
        StateManager::getInstance()->setInfo("file cannot be opened");
    }
}

void ProgrammForm::loadFile(QString path)
{
    if (QFile::exists(path))
    {

        StateManager::getInstance()->setProgrammName(path);

        QFile loadFile(path);
        if (!loadFile.open(QIODevice::ReadOnly))
        {
            StateManager::getInstance()->setIconState(StateManager::Icon::FAULT, true);
            StateManager::getInstance()->setInfo("file cannot be opened");
            return;
        }
        QByteArray loadData = loadFile.readAll();
        loadFile.close();
        QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
        QJsonObject obj = loadDoc.object();

        QJsonArray arry = obj["items"].toArray();
        for (QJsonArray::iterator i = arry.begin(); i != arry.end(); i++)
        {
            QWidget *widget = ui->commandsWidget->widget((*i).toObject()["index"].toInt());
            model->insertCommand(ui->tableView->currentIndex(),
                                 static_cast<ICommandForm *>(widget)->createCommand((*i).toObject()["index"].toInt()));
            model->getCommand(i-arry.begin())->fromJSON((*i).toObject());
        }
    }
}
