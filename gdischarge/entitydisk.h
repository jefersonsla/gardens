#ifndef ENTITYDISK_H
#define ENTITYDISK_H

#include <QStringList>

class EntityDisk
{
public:
    EntityDisk();

    void setDiskName();
    void setDiskFileSystem();
    void setDiskCapacity();
    void setDiskFreeSpace();
    void setDiskFreePercent();
    void setDiskType();

    void setTotalDiskFiles();

private:
    QStringList m_DiskName;
    QStringList m_DiskFileSystem;
    QStringList m_DiskCapacity;
    QStringList m_DiskSpace;
    QStringList m_DiskPercent;
    QStringList m_DiskType;

    QStringList m_totalDiskFiles;
};

#endif // ENTITYDISK_H
