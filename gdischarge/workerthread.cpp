#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent) : QObject(parent)
{

}

WorkerThread::~WorkerThread()
{
}

//void WorkerThread::startWorkInAThread()
//{
//    WorkerThread *workerThread = new WorkerThread(this);
//    QObject::connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
//    QObject::connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
//    workerThread->start();
//}

void WorkerThread::run()
{
    for (int i = 0; i < 1000000; ++i){
        emit resultReady(i);
    }
}
