#include "gdischargeservice.h"
#include "channelthreadone.h"
#include "logger.h"

#include <QStorageInfo>
#include <QDir>
#include <QDirIterator>
#include <QDebug>

//FAZ A LEITURA DE TODOS OS DISPOSITIVOS USB/SDCARD CONECTADOS
void GDischargeService::readAllDisk()
{
    foreach(const QStorageInfo &storage, QStorageInfo::mountedVolumes())
    {
        auto volumeDisk = storage.rootPath();
        QString mediaMounted = "/media/" + qgetenv("USER") + "/";
        QStringRef mountedDisk(&volumeDisk, 0, mediaMounted.size());

        if(mountedDisk == mediaMounted)
        {
            m_DirectoryDisk.push_back(storage.rootPath());
            m_NameDisks.push_back(storage.displayName());
        }
    }
}

void GDischargeService::StartChannel(ChannelThreadOne *pThread, QString from, QString to, QString path)
{
    if(!pThread->isRunning())
    {
        pThread->setDiskFromTo(from, to, path);
        pThread->resumeTask();
        pThread->start();
    }
    else
    {
        Logger::log("[WARNING]Copia nao iniciada pois já está em uso: " + from);
    }
}

void GDischargeService::StopChannel(ChannelThreadOne *pThread)
{
    if(pThread->isRunning())
        pThread->stopTask();
    else
        Logger::log("[WARNING] - Pausa nao concluida pois nao esta em uso: ");
}

//CLEAR ALL DISK FOR UPDATE COMBOBOX
void GDischargeService::clearAllDisk()
{
    m_NameDisks.clear();
    m_DirectoryDisk.clear();
}

void GDischargeService::refreshAllDisks()
{
    clearAllDisk();
    readAllDisk();
}
