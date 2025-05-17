#include "MySQL.hpp"
#include "dashboard.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    dashboard w;
    w.show();

    static MySQLClass *MySQL = new MySQLadmin();

    // QSqlQuery query; // = "SELECT * FROM test ORDER BY tAddr;";
    // query.prepare("SELECT * FROM test ORDER BY tAddr;");
    // qDebug() << "Query executed: "
    // << query.exec("SELECT * FROM test ORDER BY tAddr;");
    // query.next();
    // qDebug() << query.value(0);
    // query.next();
    // qDebug() << query.value(1);

    QVariantList result = MySQL->SELECT({
        // .SELECT = {{"tID"}, {"tName", "First Name"}, {"tAddr", "Address"}},
        .SELECT = {{"''"}, {"tAddr"}, {"AVG(tID)", "Average tID"}},
        .FROM   = {"test"},
        .WHERE  = {"tAddr = 'Home'", "tName = 'hamza'"},
        .GROUP  = {"tAddr"},
        .HAVING = {"5 < AVG(tID)"},
        .ORDER  = {{"tAddr", ASC}, {"tName", DESC}}
    });

    return a.exec();
}
