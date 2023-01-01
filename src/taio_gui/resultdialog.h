#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QMap>
namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QString outputFolder,
            QMap<QString,QStringList> outputs,
            QWidget *parent = nullptr);
    ~ResultDialog();

private slots:
    void on_resultComboBox_currentIndexChanged(int index);

    void on_ResultDialog_accepted();

private:
    QMap<QString,QStringList> values;
    Ui::ResultDialog *ui;
    QString outputFolder;
    void SaveFiles();
};

#endif // RESULTDIALOG_H
