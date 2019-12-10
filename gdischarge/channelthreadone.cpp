#include "channelthreadone.h"
#include "logger.h"

#include <QThread>
#include <QString>
#include <QDebug>
#include <QMutex>
#include <QStorageInfo>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QElapsedTimer>
#include <math.h>

ChannelThreadOne::ChannelThreadOne(QObject *parent) :
    QThread(parent), Stop(false)
{
}

void ChannelThreadOne::run()
{
    auto sourcePathSelect = m_disk_path;

    if(!sourcePathSelect.isEmpty())
    {
        cloneDirStruct(m_disk_path, m_disk_to);
        Logger::log("Disk Path: " + m_disk_path + " | Disk To: " + m_disk_to);
    }
    else
    {
        cloneDirStruct(m_disk_from, m_disk_to);
        setCopyAllFile(m_disk_from, m_disk_to);
        Logger::log("Disk Path: " + m_disk_path + " | Disk To: " + m_disk_to);
    }
}

void ChannelThreadOne::cloneDirStruct(const QString &sourcePathFileName, const QString &destinationPathFileName)
{
    QDir dir(sourcePathFileName);
    if (!dir.exists())
      return;

    bool compareString = (sourcePathFileName == m_disk_path);

    if(compareString)
    {
        QString dst_path = destinationPathFileName + QDir::separator() + dir.dirName();
        if(!dir.exists(dst_path))
        {
            dir.mkpath(dst_path);
            setCopyAllFile(sourcePathFileName, dst_path);
            emit statusCopyFiles(100);
            emit statusLSpeed(QString::number(0));
            emit statusLeftTime(QString::number(0));
        }
        else
        {
            setCopyAllFile(sourcePathFileName, dst_path);
            emit statusCopyFiles(100);
            emit statusLSpeed(QString::number(0));
            emit statusLeftTime(QString::number(0));
        }
    }
    else
    {
        foreach (QString diretorioPath, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QString dst_path = destinationPathFileName + QDir::separator() + diretorioPath;
            if(!dir.exists(dst_path))
                dir.mkpath(dst_path);

            cloneDirStruct(sourcePathFileName + QDir::separator() + diretorioPath, dst_path);
        }
        emit statusCopyFiles(100);
        emit statusLSpeed(QString::number(0));
        emit statusLeftTime(QString::number(0));
    }
}

void ChannelThreadOne::setCopyAllFile(const QString &sourcePathFileName, const QString &destinationPathFileName)
{
    emit statusTotFilesCH1(QString::number(0));
    emit statusTotFileMB(QString::number(0));
    emit statusFilesCH1(QString::number(0));
    emit statusCopyFiles(0);

    Logger::log("[INFO] - INICIO DA FUNÇÃO");
    //Prepara o array de arquivos
    QFileInfoList qtdFromList;
    QDirIterator it(sourcePathFileName, QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
    while(it.hasNext()) qtdFromList.push_back(it.next());

    QElapsedTimer elapsedTimerCopia;
    elapsedTimerCopia.start();

    QTime timeInicioCopia = QTime::currentTime(); //09:02
    int timestampInicioCopia = QTime(0, 0, 0).secsTo(timeInicioCopia);

    //1KB = /1024Bytes
    //1MB = /(1024Bytes * 1024Bytes)

    //SDCARD EM MB.
    auto totalTamanhoArquivosMB = 0;
    foreach (QFileInfo fileInfo, qtdFromList)
       //totalTamanhoArquivosMB += (fileInfo.size() / (1024 * 1024)); //confirmar se eh esse cara size()
        totalTamanhoArquivosMB += (fileInfo.size()); //confirmar se eh esse cara size()

    //Qtde de Arquivos.
    emit statusTotFilesCH1(QString::number(qtdFromList.length()));

    //Tamanho Total dos Arquivos.
    emit statusTotFileMB(QString::number((totalTamanhoArquivosMB/ (1024 * 1024))));
    emit statusLSpeed("Calculando");

    auto totalCopiadoMB = 0;
    for(int idx = 0; idx < qtdFromList.size(); ++idx)
    {
        QFileInfo fileInfo = qtdFromList.at(idx);
        QFileInfoList qtdToList;
        QDirIterator itto(destinationPathFileName, QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
        while(itto.hasNext()) qtdToList.push_back(itto.next());

        if(Stop) {  emit statusCopyFiles(0); return; } //Botao de Pausa

        auto origem = fileInfo.absoluteFilePath();
        auto destino = destinationPathFileName + fileInfo.absoluteFilePath().replace(sourcePathFileName,"");
        if(QFile::copy(origem, destino))
        {
            emit statusFilesCH1(QString::number(idx+1));
            totalCopiadoMB += fileInfo.size(); //confirmar se eh esse cara size()

            //GUI - Update Speed
            QTime timeAtualCopia    = QTime::currentTime(); //09:04
            int timestampAtualCopia = QTime(0, 0, 0).secsTo(timeAtualCopia);
            Logger::log("[INFO]  - timestampAtualCopia " + QString::number(timestampAtualCopia));

            auto timestampDiffSeg   = timestampAtualCopia - timestampInicioCopia; //120 segundos
            Logger::log("[INFO]  - timestampDiffSeg " + QString::number(timestampDiffSeg));

//            auto timeElapsedSeconds = elapsedTimerCopia.elapsed(); //millisec to second
//            Logger::log("[INFO]  - timeElapsedSeconds " + QString::number(timeElapsedSeconds));

            //auto timeMBpS           = totalCopiadoMB/timestampDiffSeg; //1MB/s
            auto timeMBpS           = (totalCopiadoMB/60)/60; //1MB/s
            Logger::log("[INFO]  - timeMBpS " + QString::number(timeMBpS));

            //emit statusLSpeed("marinho");
            emit statusLSpeed(QString::number(timeMBpS/1024));

            //GUI - Update Time Left (Tempo que falta)
            auto totalFaltanteMB = totalCopiadoMB - totalTamanhoArquivosMB; //50MB
            auto timeLeftSeg = (totalFaltanteMB / timeMBpS)*-1;             //50MB / velocidade 1MBPS = 50seg

            int totalNumberOfSeconds = timeLeftSeg / 60; //
            int seconds = totalNumberOfSeconds % 60;
            int minutes = (totalNumberOfSeconds / 60) % 60;
            int hours = (totalNumberOfSeconds / 60 / 60);

            QString timeString = QString("%1:%2:%3")
              .arg(hours, 2, 10, QChar('0'))
              .arg(minutes, 2, 10, QChar('0'))
              .arg(seconds, 2, 10, QChar('0'));

            emit statusLeftTime(timeString);

            Logger::log("[INFO]  - | TOT_DISC " + QString::number(totalTamanhoArquivosMB) +
                                 " | TOT_CP_MB " + QString::number(totalCopiadoMB/(1024*1024)) +
                                // " | TM_ELAP_SEC / 1000 " + QString::number(timeElapsedSeconds / 1000) +
                                 " | SPEED " + QString::number(timeMBpS) +
                                 " | TOT_LEFT_MB " + QString::number(totalFaltanteMB/(1024*1024)) +
                                 " | TM_LEFTSEC " + QString::number(timeLeftSeg) +
                                 " | NovoTempo " + timeString
                                );
            //GUI - Update Percent
            auto percent = ceil(((float)((float)qtdToList.size()/(float)qtdFromList.size())*100));
            emit statusCopyFiles(percent);
        }
        else
        {
            Logger::log("[ERROR] - Erro ao copiar arquiv: " + destino);
        }

    }

    emit statusCopyFiles(0);
    Logger::log("[INFO]  -  FINAL DA FUNÇÃO");
}
