#include "mainwindow.h"
#include "settingsdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.showMaximized();
    w.show();
    SettingsDialog dlg;
    dlg.show();
    return a.exec();
}
