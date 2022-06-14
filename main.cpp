#include "mainwindow.h"
#include <QApplication>
#include "statusview3.h"
#include "statusviewrubbishboat3.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.showMaximized();
//    w.show();

//    StatusView3 *sView = new StatusView3();
//    sView->show();

    StatusViewRubbishBoat3 *sView = new StatusViewRubbishBoat3();
    sView->show();

//    StatusView2 *s2 = new StatusView2;
//    s2->show();
    return a.exec();
}
