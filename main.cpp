#include "DatabaseManager.h"
#include "dashboard.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dashboard w;
    w.show();

    DatabaseManager &Database = DatabaseManager::Instance();

    if (Database.Connect("localhost", "mydb", "root", "khalid")) {
        qDebug() << "Successful\n";
        QVariantList products =
            Database.Select("products", {"ProductID", "Name", "Category"}, {},
                            "date_added DESC", 10, "");
        qDebug() << products;
    } else {
        qDebug() << "Unsuccesful\n";
    }

    return a.exec();
}
