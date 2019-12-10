#include <QApplication>
#include "mainwindow.h"
#include "keypress.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon(":/icon/icon/img001.ico"));
    w.setWindowTitle("GDischarge - GD.V1.2.B0001.QR1.H1");
    w.setWindowFlags(Qt::Window | Qt::WindowTitleHint );
    w.showFullScreen();

    return app.exec();
}
