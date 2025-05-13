#include "Dashboard.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    int id = QFontDatabase::addApplicationFont(":/fonts/Poppins-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    qDebug() << "Loaded font:" << family;

    QFont appFont(family);

    a.setFont(appFont);

    // Your MainWindow or app init
    dashboard w;
    w.show();

    return a.exec();
}
