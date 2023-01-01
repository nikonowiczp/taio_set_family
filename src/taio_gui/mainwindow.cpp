#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"
#include <QFileDialog>

// Magia, nie wiem czemu to pomaga ale pomaga
extern "C" {
    #include "SetRunner.h"
}
QStringList MainWindow::currentLines = QStringList();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    chosenFolder = QDir::currentPath();
    ui->setupUi(this);
    ui->outputFolderLineEdit->setText(chosenFolder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chooseOutputFolderButton_clicked(){
    chosenFolder = QFileDialog::getExistingDirectory(
                this,
                "Wybierz folder do zapisania wyników",
                nullptr);
    ui->outputFolderLineEdit->setText(chosenFolder);

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
    qDebug()<<outputs;
    auto dialog = new ResultDialog(chosenFolder, outputs ,this);
    dialog->show();
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
void MainWindow::runSimulationForFile(QString fileName){
    QByteArray fileArray = fileName.toLocal8Bit();
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        printLineToOutput(line.toLocal8Bit().data());
    }
    file.close();

    RunSet(fileArray.data(), METRIC_ALL, printLineToOutput);
    saveOutput(fileName);
}
void MainWindow::printLineToOutput(const char * format, ...){
    char buffer[256];

    va_list argptr;
    va_start(argptr, format);
    QString str;
    str.vsprintf(format, argptr);
    //vsnprintf (buffer, 255, format, argptr);
    qDebug()<<str;
    //str =  str.sprintf(format, argptr);
    //str = str.trimmed();
    //qDebug() << str;
    currentLines.append(str);
    va_end(argptr);
}

void MainWindow::saveOutput(QString fileName){
    QStringList outputList = currentLines;
    outputs.insert(fileName, outputList);
    currentLines.clear();
}

