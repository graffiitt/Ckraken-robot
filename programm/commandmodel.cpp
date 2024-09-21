#include "commandmodel.h"

CommandModel::CommandModel(/* args */)
{
}

CommandModel::~CommandModel()
{
}

void CommandModel::insertCommand(QModelIndex ind, ICommand *cmd)
{
    beginInsertRows(QModelIndex(), commands.size()-1, commands.size()-1);
    commands.insert(ind.row(), cmd);
    endInsertRows();
}

void CommandModel::updateData()
{
    dataChanged(QModelIndex(), QModelIndex());
}

ICommand *CommandModel::getCommand(const QModelIndex &ind)
{
    if(commands.size() == 0)
    return nullptr;
    return commands.at(ind.row());
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
