#include "resultdialog.h"
#include "ui_resultdialog.h"
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

#include <QDir>
ResultDialog::ResultDialog(QString outputFolder, QMap<QString,QStringList> outputs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
    values = outputs;
    ui->resultComboBox->addItems(outputs.keys());
    this->outputFolder = outputFolder;
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::on_resultComboBox_currentIndexChanged(int index)
{
    qDebug()<<"Now index is "<<index<<" and name is "<< ui->resultComboBox->currentText();
    ui->outputTextEdit->setText(values.find(ui->resultComboBox->currentText())->join("\n"));
}

void ResultDialog::SaveFiles(){
    foreach(auto fileName, values.keys()){
        QFileInfo fileInfo(fileName);
        QDir output = QDir(outputFolder);
        QString outputFile = QString("%1/%2.out.txt").arg(outputFolder).arg(fileInfo.baseName());
        qDebug()<<outputFile;
        QFile file(outputFile);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
            QMessageBox::critical(this,"Błąd", "Błąd w trakcie zapisywania do pliku");
            return;
        }
        QTextStream out(&file);
        out << values.value(fileName).join("/n");
        file.flush();
        file.close();
    }
}

void ResultDialog::on_ResultDialog_accepted()
{
    SaveFiles();
}

