#ifndef PROGRAMMFORM_H
#define PROGRAMMFORM_H

#include <QStandardPaths>
#include <QWidget>
#include <QDebug>

#include "commandmodel.h"
#include "iexecutor.h"

#include "commentform.h"
#include "timeform.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ProgrammForm;
}
QT_END_NAMESPACE

class ProgrammForm : public QWidget
{
    Q_OBJECT

public:
    ProgrammForm(QWidget *parent = nullptr);
    ~ProgrammForm();

    void openProgramm();
    void saveProgramm();
    void saveAsProgramm();
    void createNewProgramm();

signals:
    void changeEditMode(bool);

private:
    QString pathProgramm;
    QString pathFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
                         "/GraffitRobotics";

    Ui::ProgrammForm *ui;
    TimeForm *timeWidget;
    CommentForm *commentWidget;
    CommandModel *model;

    IExecutor *executor;

    void on_stopCommand();
    void on_runCommand();
    void on_createCommand();
    void on_deleteCommand();
    void on_itemClicked(const QModelIndex &index);
    void on_changeLine(int num);

    void writeFile(QString path);
    void loadFile(QString path);
};
#endif
