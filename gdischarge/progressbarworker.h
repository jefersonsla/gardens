#ifndef PROGRESSBARWORKER_H
#define PROGRESSBARWORKER_H

#include "mainwindow.h"
#include <QRunnable>
#include <QThread>
#include <QThreadPool>
#include <QProgressBar>

class ProgressBarWorker : public QThread
{
    Q_OBJECT
protected:

private slots:
    void doWork();

public:
    ProgressBarWorker() : myObject(new QObject())
    {

    }

private:
    QObject *myObject;
//    void run();
};

#endif // PROGRESSBARWORKER_H
