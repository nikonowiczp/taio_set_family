#include "calculatingworker.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Magia, nie wiem czemu to pomaga ale pomaga
extern "C" {
    #include "SetRunner.h"
}
QStringList CalculatingWorker::currentLines = QStringList();

CalculatingWorker::CalculatingWorker(QObject *parent)
    : QObject{parent}
{
    outputs = new QMap<QString, QStringList>();
}
void CalculatingWorker::doWork(const QStringList &parameters){
           foreach(auto file, parameters){
               runSimulationForFile(file);
           }

           emit resultReady(outputs);
}

void CalculatingWorker::runSimulationForFile(QString fileName){
    QByteArray fileArray = fileName.toLocal8Bit();
    RunSet(fileArray.data(), METRIC_ALL, printLineToOutput);
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        printLineToOutput(line.toLocal8Bit().data());
    }
    file.close();
    saveOutput(fileName);
}
void CalculatingWorker::printLineToOutput(const char * format, ...){
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

void CalculatingWorker::saveOutput(QString fileName){
    QStringList outputList = currentLines;
    outputs->insert(fileName, outputList);
    currentLines.clear();
}
