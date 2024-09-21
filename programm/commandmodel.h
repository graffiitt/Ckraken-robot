#ifndef COMMANDMODEL_H
#define COMMANDMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "commands/icommand.h"

class CommandModel : public QAbstractTableModel
{
public:
    CommandModel(/* args */);
    ~CommandModel();

    void insertCommand(QModelIndex ind, ICommand* cmd);
    void updateData();
    ICommand* getCommand(const QModelIndex &ind);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    QList<ICommand*> commands;

};




#endif