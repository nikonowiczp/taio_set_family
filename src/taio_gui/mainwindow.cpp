#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    chosenFolder = QDir::currentPath();
    ui->setupUi(this);
    ui->outputFolderLineEdit->setText(chosenFolder);
    CalculatingWorker *worker = new CalculatingWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::operate, worker, &CalculatingWorker::doWork);
    connect(worker, &CalculatingWorker::resultReady, this, &MainWindow::handleResults);
    workerThread.start();
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
    setLoading(false);

    emit this->operate(*ChosenFiles);
}

void MainWindow::on_simulateChosenButton_clicked(){
    qDebug() << "Simulate one button clicked";

}

void MainWindow::addFileToList(QString file){
    if(!ChosenFiles->contains(file)){
        qDebug()<<"Adding file "<< file;
        ChosenFiles->append(file);
        ui->listWidget->addItem(file);
    }

}

void MainWindow::addFilesToList(QStringList files){
    foreach(auto file, files){
        addFileToList(file);
    }
}

void MainWindow::handleResults(const QMap<QString, QStringList> *outputs){
    QMap<QString, QStringList> result = *outputs;
    auto dialog = new ResultDialog(chosenFolder, result ,this);
    dialog->show();
    setLoading(true);
}
void MainWindow::setLoading(bool newState){
    ui->chooseFilesButton->setEnabled(newState);
    ui->chooseFolderButton->setEnabled(newState);
    ui->chooseOutputFolderButton->setEnabled(newState);
    ui->simulateAllButton->setEnabled(newState);
}
