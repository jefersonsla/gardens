#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gdischargeservice.h"
#include "channelthreadone.h"
#include "keypress.h"

#include <QMainWindow>
#include <vector>
#include <map>
#include <QProgressBar>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFileSystemWatcher>
#include <QDebug>
#include <QLabel>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void unitTestDisks();
    void refreshAllChannels();
    int getAvailableSlot(QString disk);
    QString getVirtualDisk(QString disk);
    QString getVolume(QString virtualDisk);
    QStringList getMountedVolumes();

private slots:
    //BUTTON "FECHAR PROGRAMA"
    void on_btnFecharPrograma_clicked();

    //BUTTON "STOP CÓPIA"
    void on_btnStopChannel1_clicked();
    void on_btnStopChannel2_clicked();
    void on_btnStopChannel3_clicked();
    void on_btnStopChannel4_clicked();
    void on_btnStopChannel5_clicked();
    void on_btnStopChannel6_clicked();
    void on_btnStopChannel7_clicked();
    void on_btnStopChannel8_clicked();

    //BUTTON "PLAY CÓPIA"
    void on_btnIniciaCopiaChannel1_clicked();
    void on_btnIniciaCopiaChannel2_clicked();
    void on_btnIniciaCopiaChannel3_clicked();
    void on_btnIniciaCopiaChannel4_clicked();
    void on_btnIniciaCopiaChannel5_clicked();
    void on_btnIniciaCopiaChannel6_clicked();
    void on_btnIniciaCopiaChannel7_clicked();
    void on_btnIniciaCopiaChannel8_clicked();

    //BUTTON "PASTA DE ORIGEM"
    void on_btnPastaDeOrigemChannel1_clicked();
    void on_btnPastaDeOrigemChannel2_clicked();
    void on_btnPastaDeOrigemChannel3_clicked();
    void on_btnPastaDeOrigemChannel4_clicked();
    void on_btnPastaDeOrigemChannel5_clicked();
    void on_btnPastaDeOrigemChannel6_clicked();
    void on_btnPastaDeOrigemChannel7_clicked();
    void on_btnPastaDeOrigemChannel8_clicked();

    //BUTTON "PASTA DE DESTINO"
    void on_btnPastaDeDestinoChannel2_clicked();
    void on_btnPastaDeDestinoChannel1_clicked();
    void on_btnPastaDeDestinoChannel3_clicked();
    void on_btnPastaDeDestinoChannel4_clicked();
    void on_btnPastaDeDestinoChannel5_clicked();
    void on_btnPastaDeDestinoChannel6_clicked();
    void on_btnPastaDeDestinoChannel7_clicked();
    void on_btnPastaDeDestinoChannel8_clicked();

    void directoryChanged(const QString &path);
    void updateCloseButton(const QString &text);

    //void on_progressBarChannel1_windowIconTextChanged(const QString &iconText);

private:
    Ui::MainWindow *ui;
    QFileSystemWatcher *watcher;
    GDischargeService DischargeService;
    ChannelThreadOne m_vThread1, m_vThread2, m_vThread3, m_vThread4, m_vThread5, m_vThread6, m_vThread7, m_vThread8;
    map<QString, int> m_Slots;
    map<QString, QString> m_VirtualDisks;
    QLabel *myLabelText;


    void initGUI();
    void refreshComboItems(QComboBox *pComboChannel);
    void openDialogFolder(QLineEdit *pLineEdit);
    void openDialogFolderOrigem(QLineEdit *pLineEdit, QComboBox *pComboBox);
    void initChannel(ChannelThreadOne *pThread,
                     QProgressBar *pPBChannel,
                     QLineEdit *pLineEditTxt,
                     QPushButton *pPushButton,
                     QComboBox *pComboChannel,
                     QLabel *pLabelFilesCH1 = NULL,
                     QLabel *pLabelTotFilesCH = NULL,
                     QLabel *pLabelTotFileMBCH = NULL,
                     QLabel *pLabelLeftTime = NULL,
                     QLabel *pLabelCH = NULL,
                     QLabel *pLabelLoadingCH1 = NULL
                      );
    void monitorResolution();
};

#endif // MAINWINDOW_H
