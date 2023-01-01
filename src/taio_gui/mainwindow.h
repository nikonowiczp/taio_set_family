#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void runSimulationForFile(QString file);
    void addFileToList(QString file);
    void addFilesToList(QStringList files);
    static void printLineToOutput(const char * format, ...);

private slots:
    void on_chooseFilesButton_clicked();
    void on_chooseFolderButton_clicked();
    void on_simulateAllButton_clicked();
    void on_simulateChosenButton_clicked();
};
#endif // MAINWINDOW_H
