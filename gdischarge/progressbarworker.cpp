#include "progressbarworker.h"
#include "ui_mainwindow.h"
#include <QDirIterator>
#include <QDebug>

ProgressBarWorker::ProgressBarWorker(QProgressBar *pb_control, QString originPath, QString destinPath)
{
     this->pb_porcentagem = pb_control;
     this->m_originPath = originPath;
     this->m_destinPath = destinPath;
}

void ProgressBarWorker::run()
{
    QStringList filesOrigin = {};
    QDirIterator it(m_originPath, QStringList() << "*.avi", QDir::NoFilter, QDirIterator::Subdirectories);
    while(it.hasNext())
        filesOrigin.push_back(it.fileName());

    QStringList filesDestin = {};
    QDirIterator itd(m_originPath, QStringList() << "*.avi", QDir::NoFilter, QDirIterator::Subdirectories);
    while(itd.hasNext())
        filesDestin.push_back(itd.fileName());

    int qtdOrigin = filesOrigin.size(); // 15
    int qtdDestin = filesDestin.size(); // 7

    while(qtdDestin < qtdOrigin)
    {
        qDebug() << "Hello from thread " << QThread::currentThread();

        int percent = (qtdDestin / qtdOrigin) * 100;
        pb_porcentagem->setValue(percent);

        QThread::sleep(1);
    }
}
