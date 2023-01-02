#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "resultdialog.h"
#include <QThread>
#include "calculatingworker.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<QString> *ChosenFiles = new QList<QString>();
    QString chosenFolder = "";

    void addFileToList(QString file);
    void addFilesToList(QStringList files);
    QThread workerThread;
    void setLoading(bool newState);
private slots:
    void on_chooseFilesButton_clicked();
    void on_chooseFolderButton_clicked();
    void on_simulateAllButton_clicked();
    void on_simulateChosenButton_clicked();
    void on_chooseOutputFolderButton_clicked();
public slots:
    void handleResults(const QMap<QString, QStringList> * result);
signals:
    void operate(const QStringList &);

};
#endif // MAINWINDOW_H
