#include "commandmodel.h"
#include <QDebug>

CommandModel::CommandModel(/* args */)
{
}

CommandModel::~CommandModel()
{
}

void CommandModel::insertCommand(QModelIndex ind, ICommand *cmd)
{
    beginInsertRows(QModelIndex(), commands.size() - 1, commands.size() - 1);
    if (ind.row() == -1)
        commands.append(cmd);
    else
        commands.insert(ind.row(), cmd);
    endInsertRows();
}

void CommandModel::deleteCommand(QModelIndex ind)
{
    if (ind.row() == -1)
        return;
    beginRemoveRows(QModelIndex(), ind.row(), ind.row());
    delete commands.takeAt(ind.row());
    endRemoveRows();
}

void CommandModel::deleteAllCommands()
{
    beginRemoveRows(QModelIndex(), 0, commands.size()-1);
    qDeleteAll(commands);
    commands.clear();
    endRemoveRows();
}

void CommandModel::updateData()
{
    dataChanged(QModelIndex(), QModelIndex());
}

ICommand *CommandModel::getCommand(const QModelIndex &ind)
{
    if (commands.size() == 0)
        return nullptr;
    return commands.at(ind.row());
}

ICommand *CommandModel::getCommand(const int index)
{
    if (commands.size() == 0)
        return nullptr;
    return commands.at(index);
}

int CommandModel::rowCount(const QModelIndex &parent) const
{
    return commands.size();
}

int CommandModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant CommandModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
    {
        return commands.at(index.row())->getStroke();
    }
    default:
        return QVariant();
    }
}
