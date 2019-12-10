#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = nullptr);
    ~WorkerThread();

protected:
    void run();

signals:
    void resultReady(int);
};

#endif // WORKERTHREAD_H
