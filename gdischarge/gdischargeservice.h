#ifndef GDISCHARGESERVICE_H
#define GDISCHARGESERVICE_H

#include "channelthreadone.h"

#include <QStringList>
#include <QString>

class GDischargeService
{
public:
    //SET - Setters
    void StartChannel(ChannelThreadOne *pThread, QString from, QString to, QString path);
    void StopChannel(ChannelThreadOne *pThread);
    void readAllDisk();
    void clearAllDisk();
    void refreshAllDisks();
    void updateAllDisks();

    //GET - Getters
    QStringList getNameDisks() const { return m_NameDisks; }
    QStringList getDirectoryDisk() const { return m_DirectoryDisk; }

private:
    QStringList m_NameDisks;
    QStringList m_DirectoryDisk;
};

#endif // GDISCHARGESERVICE_H
