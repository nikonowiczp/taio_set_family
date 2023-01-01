#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"
#include <QFileDialog>
#include "SetRunner.h"

// Magia, nie wiem czemu to pomaga ale pomaga
extern "C" {
    #include "SetParser.h"
    #include "TaioData.h"
    #include "TaioHashMap.h"
    #include "TaioSetList.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include "taioalgorithms.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_chooseFilesButton_clicked(){
    qDebug() << "Choose files button clicked";
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "Wybierz jeden lub więcej plik do otwarcia",
                            nullptr,
                            "Text files (*.txt );;Any files (*)");

    qDebug()<<files;
    addFilesToList(files);
}

void MainWindow::on_chooseFolderButton_clicked(){
    qDebug() << "Choose folder button clicked";
    QString directoryPath = QFileDialog::getExistingDirectory(
                            this,
                            "Wybierz folder do otwarcia",
                            nullptr);
    QDir directory(directoryPath);
    auto files = directory.entryInfoList(QStringList() << "*.txt",QDir::Files);

    qDebug()<<files;
    foreach(auto file, files){
        addFileToList(file.absoluteFilePath());

    }
}
void MainWindow::on_simulateAllButton_clicked(){
    qDebug() << "Simulate all button clicked";
    foreach(auto file, *ChosenFiles){
        runSimulationForFile(file);
    }

}
void MainWindow::on_simulateChosenButton_clicked(){
    qDebug() << "Simulate one button clicked";

}
void MainWindow::addFileToList(QString file){
    qDebug()<<"Adding file "<< file;
    ChosenFiles->append(file);
    ui->listWidget->addItem(file);
}
void MainWindow::addFilesToList(QStringList files){
    foreach(auto file, files){
        addFileToList(file);
    }
}
void MainWindow::runSimulationForFile(QString file){
    QByteArray fileArray = file.toLocal8Bit();

    RunSet(fileArray.data(), METRIC_ALL, printLineToOutput);
}
void MainWindow::printLineToOutput(const char * format, ...){
    va_list argptr;
    va_start(argptr, format);
    qDebug(format, argptr);
    va_end(argptr);
}
