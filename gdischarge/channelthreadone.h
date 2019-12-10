#ifndef CHANNELTHREADONE_H
#define CHANNELTHREADONE_H

#include <QThread>
#include <QString>

class ChannelThreadOne : public QThread
{
    Q_OBJECT
public:
    ChannelThreadOne(QObject *parent = 0);
    void run();

    void setDiskFromTo(QString &from, QString &to, QString &path) { m_disk_from = from; m_disk_to = to; m_disk_path = path; }
    void cloneDirStruct(const QString &sourcePathFileName, const QString &destinationPathFileName);
    void setCopyAllFile(const QString &sourcePathFileName, const QString &destinationPathFileName);
    void stopTask(){ Stop = true; }
    void resumeTask(){ Stop = false; }

    void copyAllDir();
    void copyAllFiles();

signals:
    void valueChanged(int);
    void statusCopyFiles(int);     //conectou num progress bar
    void statusLeftTime(QString);  //conectou numa slot do main windows e formate o texto (resultado INT + 1minXsegundos)
    void statusFilesCH1(QString);
    void statusTotFilesCH1(QString);
    void statusTotFileMB(QString);
    void statusLSpeed(QString);    //conectou numa slot do main windows e formate o texto (resultado INT + KBPS)
    void statusLoading(QString);

private:
    bool Stop;
    QString m_disk_from;
    QString m_disk_to;
    QString m_disk_path;
};

#endif // CHANNELTHREADONE_H
