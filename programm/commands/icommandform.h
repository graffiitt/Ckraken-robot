#ifndef ICOMMANDFORM_H
#define ICOMMANDFORM_H

#include <QWidget>
#include <QString>
#include "icommand.h"

class ICommandForm: public QWidget
{
    Q_OBJECT
public:
    ICommandForm(QString name, QWidget* parent = nullptr) : QWidget(parent), nameCommand(name) {};
    virtual ~ICommandForm() {};
    QString getName() { return nameCommand; };

    virtual void setCommand(ICommand *cmd) = 0;
    virtual ICommand *createCommand(int index) = 0;

public slots:
     void setEditing(bool state) { this->setEnabled(state); };

signals:
    void dataChanged();

private:
    QString nameCommand;
};

#endif