#ifndef CALCULATINGWORKER_H
#define CALCULATINGWORKER_H

#include <QObject>
#include <QMap>
#include "stringlistmap.h"

class CalculatingWorker : public QObject
{
    Q_OBJECT
public:
    explicit CalculatingWorker(QObject *parent = nullptr);
    static void printLineToOutput(const char * format, ...);
    static QStringList currentLines;

public slots:
    void doWork(const QStringList &parameters);

private:
    void runSimulationForFile(QString file);
    void saveOutput(QString fileName);
    QMap<QString, QStringList>* outputs;

signals:
    void resultReady(const QMap<QString, QStringList> *output);

};

#endif // CALCULATINGWORKER_H
