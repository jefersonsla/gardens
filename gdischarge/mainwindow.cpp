#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"

#include <QString>
#include <QStringList>
#include <QStorageInfo>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QStandardPaths>
#include <QInputDialog>
#include <QFileInfo>
#include <QSize>
#include <QDesktopWidget>
#include <vector>
#include <QPlainTextEdit>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //LOG
    QPlainTextEdit *editor = new QPlainTextEdit(this);
    editor->hide();
    Logger::initLogger(this, editor);
    Logger::log("[INICIALIZAÇÃO] - GDISCHARGE - V2.01 - Initializing");

    initGUI();           //Inicialização do sistema ...
    monitorResolution(); //Resolução automática do monitor utilizado ...

    myLabelText = new QLabel("You Didn't Pressed / Released any Key");
}

//INICIALIZAÇÃO DO SOFTWARE E TODAS AS FUNÇÕES ...
void MainWindow::initGUI()
{
    DischargeService.readAllDisk();

    initChannel(&m_vThread1,
                ui->progressBarChannel1,
                ui->txtPastaDeDestinoChannel1,
                ui->btnIniciaCopiaChannel1,
                ui->comboBoxCardChannel1,
                ui->lbFilesCH1,
                ui->lbTOTFilesCH1,
                ui->lbTOTFileMBCH1,
                ui->lbLeftTimeCH1,
                ui->lbTimeCH1);
      initChannel(&m_vThread2,
                  ui->progressBarChannel2,
                  ui->txtPastaDeDestinoChannel2,
                  ui->btnIniciaCopiaChannel2,
                  ui->comboBoxCardChannel2,
                  ui->lbFilesCH2,
                  ui->lbTOTFilesCH2,
                  ui->lbTOTFileMBCH2,
                  ui->lbLeftTimeCH2,
                  ui->lbTimeCH2);
      initChannel(&m_vThread3,
                  ui->progressBarChannel3,
                  ui->txtPastaDeDestinoChannel3,
                  ui->btnIniciaCopiaChannel3,
                  ui->comboBoxCardChannel3,
                  ui->lbFilesCH3,
                  ui->lbTOTFilesCH3,
                  ui->lbTOTFileMBCH3,
                  ui->lbLeftTimeCH3,
                  ui->lbTimeCH3);
      initChannel(&m_vThread4,
                  ui->progressBarChannel4,
                  ui->txtPastaDeDestinoChannel4,
                  ui->btnIniciaCopiaChannel4,
                  ui->comboBoxCardChannel4,
                  ui->lbFilesCH4,
                  ui->lbTOTFilesCH4,
                  ui->lbTOTFileMBCH4,
                  ui->lbLeftTimeCH4,
                  ui->lbTimeCH4);
      initChannel(&m_vThread5,
                  ui->progressBarChannel5,
                  ui->txtPastaDeDestinoChannel5,
                  ui->btnIniciaCopiaChannel5,
                  ui->comboBoxCardChannel5,
                  ui->lbFilesCH5,
                  ui->lbTOTFilesCH5,
                  ui->lbTOTFileMBCH5,
                  ui->lbLeftTimeCH5,
                  ui->lbTimeCH5);
      initChannel(&m_vThread6,
                  ui->progressBarChannel6,
                  ui->txtPastaDeDestinoChannel6,
                  ui->btnIniciaCopiaChannel6,
                  ui->comboBoxCardChannel6,
                  ui->lbFilesCH6,
                  ui->lbTOTFilesCH6,
                  ui->lbTOTFileMBCH6,
                  ui->lbLeftTimeCH6,
                  ui->lbTimeCH6);
      initChannel(&m_vThread7,
                  ui->progressBarChannel7,
                  ui->txtPastaDeDestinoChannel7,
                  ui->btnIniciaCopiaChannel7,
                  ui->comboBoxCardChannel7,
                  ui->lbFilesCH7,
                  ui->lbTOTFilesCH7,
                  ui->lbTOTFileMBCH7,
                  ui->lbLeftTimeCH7,
                  ui->lbTimeCH7);
      initChannel(&m_vThread8,
                  ui->progressBarChannel8,
                  ui->txtPastaDeDestinoChannel8,
                  ui->btnIniciaCopiaChannel8,
                  ui->comboBoxCardChannel8,
                  ui->lbFilesCH8,
                  ui->lbTOTFilesCH8,
                  ui->lbTOTFileMBCH8,
                  ui->lbLeftTimeCH8,
                  ui->lbTimeCH8);

    refreshAllChannels();

    watcher = new QFileSystemWatcher(this);
    watcher->addPath("/media/" + qgetenv("USER") + "/");
    connect(watcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(directoryChanged(const QString &)));

    ui->statusBar->showMessage("GDischarge ...");
}

QStringList MainWindow::getMountedVolumes()
{
    return DischargeService.getDirectoryDisk();
}

QString MainWindow::getVirtualDisk(QString disk)
{
    QString virtualDisk = "";

    if(m_VirtualDisks.find(disk) != m_VirtualDisks.end())
    {
        virtualDisk = m_VirtualDisks[disk];
        Logger::log("m_VirtualDisks[disk]: " + virtualDisk);
    }
    else
    {
        int availableSlot = m_VirtualDisks.size() + 1;

        for(int value = 0x43/*C:*/; value <= 0x4A; ++value)
        {
            auto itd = m_VirtualDisks.begin();
            bool bFound = false;

            // Iterate through the map
            while(itd != m_VirtualDisks.end())
            {
                // Check if value of this entry matches with given value
                QString currentDisk = itd->second;
                auto asciiValue = (int)currentDisk.toLocal8Bit()[0];
                if( asciiValue == value)
                {
                    bFound = true;
                }
                itd++;
            }

            if(!bFound)
            {
                availableSlot = value;
                break;
            }
        }

        m_VirtualDisks.insert( std::make_pair(disk, static_cast<char>(availableSlot)) );
        virtualDisk = m_VirtualDisks[disk];

    }

    return virtualDisk;
}

QString MainWindow::getVolume(QString virtualDisk)
{
    auto itd = m_VirtualDisks.begin();

    // Iterate through the map
    while(itd != m_VirtualDisks.end())
    {
        // Check if value of this entry matches with given value
        QString currentDisk = itd->second;

        if( currentDisk == virtualDisk)
        {
            return itd->first;
        }
        itd++;
    }

    return "";
}

int MainWindow::getAvailableSlot(QString disk)
{
    int slot = -1;

    if(m_Slots.find(disk) != m_Slots.end())
    {
        slot = m_Slots[disk];
    }
    else
    {
        int availableSlot = m_Slots.size() + 1;
        int qtdMslot = m_Slots.size();

        for(int value = 1; value <= qtdMslot; ++value)
        {
            auto it = m_Slots.begin();
            bool bFound = false;

            // Iterate through the map
            while(it != m_Slots.end())
            {
                // Check if value of this entry matches with given value
                if(it->second == value)
                {
                    bFound = true;
                }
                it++;
            }

            if(!bFound)
            {
                availableSlot = value;
                break;
            }
        }
        if(availableSlot > (qtdMslot + 1))
            return -1;

        m_Slots.insert( std::make_pair(disk, availableSlot) );
        slot = m_Slots[disk];
        Logger::log("Slot: " + m_Slots[disk]);
    }

    return slot;
}

void MainWindow::unitTestDisks()
{
    QStringList volumes = getMountedVolumes();

    m_Slots.insert(std::make_pair("F:", 2));
    m_Slots.insert(std::make_pair("G:", 1));
    m_Slots.insert(std::make_pair("H:", 4));
    m_Slots.insert(std::make_pair("E:", 6));

    foreach(auto volume, volumes)
    {
        int slot = getAvailableSlot(getVirtualDisk(volume));
        qDebug() << "DISK: " << volume << " | SLOT: " << slot ;
    }
}

void MainWindow::monitorResolution()
{
    QSize availableSize = qApp->desktop()->availableGeometry().size();

    int width   = availableSize.width();
    int height  = availableSize.height();

    width *= 1.0;  // 100% of the screen size
    height *= 1.0; // 100% of the screen size

    QSize newSize( width, height );
    setGeometry( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, newSize, qApp->desktop()->availableGeometry()));
}

void MainWindow::refreshAllChannels()
{
    DischargeService.refreshAllDisks();
    QStringList nameDisks = DischargeService.getDirectoryDisk();

    ui->comboBoxCardChannel1->clear();
    ui->comboBoxCardChannel2->clear();
    ui->comboBoxCardChannel3->clear();
    ui->comboBoxCardChannel4->clear();
    ui->comboBoxCardChannel5->clear();
    ui->comboBoxCardChannel6->clear();
    ui->comboBoxCardChannel7->clear();
    ui->comboBoxCardChannel8->clear();

    foreach(auto volume, nameDisks)
    {
        auto virtualDisk = getVirtualDisk(volume);
        int slot = getAvailableSlot(virtualDisk);

        switch (slot)
        {
        case 1:
            ui->comboBoxCardChannel1->addItem(virtualDisk);
            break;
        case 2:
            ui->comboBoxCardChannel2->addItem(virtualDisk);
            break;
        case 3:
            ui->comboBoxCardChannel3->addItem(virtualDisk);
            break;
        case 4:
            ui->comboBoxCardChannel4->addItem(virtualDisk);
            break;
        case 5:
            ui->comboBoxCardChannel5->addItem(virtualDisk);
            break;
        case 6:
            ui->comboBoxCardChannel6->addItem(virtualDisk);
            break;
        case 7:
            ui->comboBoxCardChannel7->addItem(virtualDisk);
            break;
        case 8:
            ui->comboBoxCardChannel8->addItem(virtualDisk);
            break;
        default:
            break;
        }
    }
}

void MainWindow::directoryChanged(const QString &path)
{
    refreshAllChannels();
    thread()->msleep(2000);
    refreshAllChannels();
}

void MainWindow::updateCloseButton(const QString &text)
{
    ui->btnIniciaCopiaChannel1->setEnabled(!text.isEmpty());
    ui->btnStopChannel1->setEnabled(!text.isEmpty());
}

//INICIAR CÓPIA DOS ARQUIVOS DOS SDCARDS CONECTADOS
void MainWindow::on_btnIniciaCopiaChannel1_clicked()
{
    DischargeService.StartChannel( &m_vThread1, getVolume(ui->comboBoxCardChannel1->currentText()), ui->txtPastaDeDestinoChannel1->text(), ui->txtPastaDeOrigemChannel1->text());
}

void MainWindow::on_btnIniciaCopiaChannel2_clicked()
{
    DischargeService.StartChannel(&m_vThread2, getVolume(ui->comboBoxCardChannel2->currentText()), ui->txtPastaDeDestinoChannel2->text(), ui->txtPastaDeOrigemChannel2->text());
}

void MainWindow::on_btnIniciaCopiaChannel3_clicked()
{
    DischargeService.StartChannel(&m_vThread3, getVolume(ui->comboBoxCardChannel3->currentText()), ui->txtPastaDeDestinoChannel3->text(), ui->txtPastaDeOrigemChannel3->text());
}

void MainWindow::on_btnIniciaCopiaChannel4_clicked()
{
    DischargeService.StartChannel(&m_vThread4, getVolume(ui->comboBoxCardChannel4->currentText()), ui->txtPastaDeDestinoChannel4->text(), ui->txtPastaDeOrigemChannel4->text());
}

void MainWindow::on_btnIniciaCopiaChannel5_clicked()
{
    DischargeService.StartChannel(&m_vThread5, getVolume(ui->comboBoxCardChannel5->currentText()), ui->txtPastaDeDestinoChannel5->text(), ui->txtPastaDeOrigemChannel5->text());
}

void MainWindow::on_btnIniciaCopiaChannel6_clicked()
{
    DischargeService.StartChannel(&m_vThread6, getVolume(ui->comboBoxCardChannel6->currentText()), ui->txtPastaDeDestinoChannel6->text(), ui->txtPastaDeOrigemChannel6->text());
}

void MainWindow::on_btnIniciaCopiaChannel7_clicked()
{
    DischargeService.StartChannel(&m_vThread7, getVolume(ui->comboBoxCardChannel7->currentText()), ui->txtPastaDeDestinoChannel7->text(), ui->txtPastaDeOrigemChannel7->text());
}

void MainWindow::on_btnIniciaCopiaChannel8_clicked()
{
    DischargeService.StartChannel(&m_vThread8, getVolume(ui->comboBoxCardChannel8->currentText()), ui->txtPastaDeDestinoChannel8->text(), ui->txtPastaDeOrigemChannel8->text());
}

//PARAR CÓPIA DOS ARQUIVOS DOS SDCARDS CONECTADOS
void MainWindow::on_btnStopChannel1_clicked()
{
    DischargeService.StopChannel(&m_vThread1);
}

void MainWindow::on_btnStopChannel2_clicked()
{
    DischargeService.StopChannel(&m_vThread2);
}

void MainWindow::on_btnStopChannel3_clicked()
{
    DischargeService.StopChannel(&m_vThread3);
}

void MainWindow::on_btnStopChannel4_clicked()
{
    DischargeService.StopChannel(&m_vThread4);
}

void MainWindow::on_btnStopChannel5_clicked()
{
    DischargeService.StopChannel(&m_vThread5);
}

void MainWindow::on_btnStopChannel6_clicked()
{
    DischargeService.StopChannel(&m_vThread6);
}

void MainWindow::on_btnStopChannel7_clicked()
{
    DischargeService.StopChannel(&m_vThread7);
}

void MainWindow::on_btnStopChannel8_clicked()
{
    DischargeService.StopChannel(&m_vThread8);
}

//SELECIONAR APENAS UMA PASTA PARA SER COPIADA PARA O DESTINO
void MainWindow::on_btnPastaDeOrigemChannel1_clicked()
{
    openDialogFolderOrigem(ui->txtPastaDeOrigemChannel1, ui->comboBoxCardChannel1);
}

void MainWindow::on_btnPastaDeOrigemChannel2_clicked()
{
    openDialogFolderOrigem(ui->txtPastaDeOrigemChannel2, ui->comboBoxCardChannel2);
}

void MainWindow::on_btnPastaDeOrigemChannel3_clicked()
{
    openDialogFolderOrigem(ui->txtPastaDeOrigemChannel3, ui->comboBoxCardChannel3);
}

void MainWindow::on_btnPastaDeOrigemChannel4_clicked()
{
    openDialogFolderOrigem(ui->txtPastaDeOrigemChannel4, ui->comboBoxCardChannel4);
}

void MainWindow::on_btnPastaDeOrigemChannel5_clicked()
{
    openDialogFolderOrigem(ui->txtPastaDeOrigemChannel5, ui->comboBoxCardChannel5);
}

void MainWindow::on_btnPastaDeOrigemChannel6_clicked()
{
    openDialogFolderOrigem(ui->txtPastaDeOrigemChannel6, ui->comboBoxCardChannel6);
}

void MainWindow::on_btnPastaDeOrigemChannel7_clicked()
{
    openDialogFolderOrigem(ui->txtPastaDeOrigemChannel7, ui->comboBoxCardChannel7);
}

void MainWindow::on_btnPastaDeOrigemChannel8_clicked()
{
    openDialogFolderOrigem(ui->txtPastaDeOrigemChannel8, ui->comboBoxCardChannel8);
}

//SELECIONA DA PASTA DE DESTINO PARA A CÓPIA DOS ARQUIVOS
void MainWindow::on_btnPastaDeDestinoChannel1_clicked()
{
    openDialogFolder(ui->txtPastaDeDestinoChannel1);
}

void MainWindow::on_btnPastaDeDestinoChannel2_clicked()
{
   openDialogFolder(ui->txtPastaDeDestinoChannel2);
}

void MainWindow::on_btnPastaDeDestinoChannel3_clicked()
{
    openDialogFolder(ui->txtPastaDeDestinoChannel3);
}

void MainWindow::on_btnPastaDeDestinoChannel4_clicked()
{
    openDialogFolder(ui->txtPastaDeDestinoChannel4);
}

void MainWindow::on_btnPastaDeDestinoChannel5_clicked()
{
    openDialogFolder(ui->txtPastaDeDestinoChannel5);
}

void MainWindow::on_btnPastaDeDestinoChannel6_clicked()
{
    openDialogFolder(ui->txtPastaDeDestinoChannel6);
}

void MainWindow::on_btnPastaDeDestinoChannel7_clicked()
{
    openDialogFolder(ui->txtPastaDeDestinoChannel7);
}

void MainWindow::on_btnPastaDeDestinoChannel8_clicked()
{
    openDialogFolder(ui->txtPastaDeDestinoChannel8);
}

//BUTTON CLOSE - FECHA/ENCERRA O SOFTWARE
void MainWindow::on_btnFecharPrograma_clicked()
{
    bool questionOk = false;

    QString text = QInputDialog::getText(this, tr("GDischarge Password"),
                                               tr("Insira senha do usuário:"),
                                         QLineEdit::Password, tr(""), &questionOk);

    if((questionOk & !text.isEmpty()) && (text == "admin"))
        QApplication::quit();
    else
        QMessageBox::critical(this, "Erro", "Senha inválida\nDigite uma senha válida");
}

//ATUALIZA A LISTA DE DISPOSITIVOS CONECTADOS
void MainWindow::refreshComboItems(QComboBox *pComboChannel)
{
    pComboChannel->clear();
    DischargeService.refreshAllDisks();
    DischargeService.getDirectoryDisk().isEmpty() ?
                pComboChannel->addItem("SDCARD DISCONNECTED") :
                pComboChannel->addItems(DischargeService.getNameDisks());
}

void MainWindow::openDialogFolderOrigem(QLineEdit *pLineEdit, QComboBox *pComboBox)
{
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::DirectoryOnly);

    QString selectSourceDisk = "/media/" + qgetenv("USER") + "/" + pComboBox->currentText();

    QString dir = QFileDialog::getExistingDirectory(this, tr("Selecionar destino da cópia"),
                                                    selectSourceDisk, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    pLineEdit->setText(dir);
}

void MainWindow::openDialogFolder(QLineEdit *pLineEdit)
{
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::DirectoryOnly);

    QString destinPath = "/home/" + qgetenv("USER") + "/Desktop/";

    QString dir = QFileDialog::getExistingDirectory(this, tr("Pasta de destino"),
                            destinPath,
                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    pLineEdit->setText(dir);
}

void MainWindow::initChannel(
        ChannelThreadOne *pThread,
        QProgressBar *pPBChannel,
        QLineEdit *pLineEditTxt,
        QPushButton *pPushButton,
        QComboBox *pComboChannel,
        QLabel *pLabelFilesCH,
        QLabel *pLabelTotFilesCH,
        QLabel *pLabelTotFileMBCH,
        QLabel *pLabelLeftTime,
        QLabel *pLabelCH,
        QLabel *pLabelLoadingCH)
{
    connect(pThread,SIGNAL(statusCopyFiles(int)),pPBChannel,SLOT(setValue(int)));
    connect(pLineEditTxt, SIGNAL(textChanged(const QString &)), this, SLOT(updateCloseButton(const QString &)));

    if(pLabelFilesCH)
    connect(pThread,SIGNAL(statusFilesCH1(QString)),pLabelFilesCH,SLOT(setText(QString)));

    if(pLabelTotFilesCH)
    connect(pThread,SIGNAL(statusTotFilesCH1(QString)),pLabelTotFilesCH,SLOT(setText(QString)));

    if(pLabelTotFileMBCH)
    connect(pThread,SIGNAL(statusTotFileMB(QString)),pLabelTotFileMBCH,SLOT(setText(QString)));

    if(pLabelLeftTime)
    connect(pThread,SIGNAL(statusLeftTime(QString)),pLabelLeftTime,SLOT(setText(QString)));

    if(pLabelCH)
    connect(pThread,SIGNAL(statusLSpeed(QString)),pLabelCH,SLOT(setText(QString)));

    QStringList nameDisks = DischargeService.getNameDisks();

    pComboChannel->clear();
    if(nameDisks.isEmpty())
        pComboChannel->addItem("SDCARD DISCONNECTED");
}

MainWindow::~MainWindow()
{
    delete ui;
}
