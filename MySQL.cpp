#include "MySQL.hpp"

bool MySQLClass::Connect(const QString &Host, const QString &DBName,
                         const QString &user, const QString &passwd) {
    this->MySQLconn = QSqlDatabase::addDatabase("QSQLITE");
    this->MySQLconn.setHostName(Host);
    this->MySQLconn.setDatabaseName(DBName);
    this->MySQLconn.setUserName(user);
    this->MySQLconn.setPassword(passwd);
    if (this->MySQLconn.open()) return false;
    else
        throw MySQLError("MySQL Connection was not opened!");
}

MySQLClass::MySQLClass() {
    if (!this->MySQLconn.isOpen()) this->Connect("", "test.sqlite3", "", "");
}

QVariantList MySQLClass::SELECT(Query query) {

    QSqlQuery sqlQuery;
    // Separate function to reduce clutter.
    this->prepareSELECTQuery(sqlQuery, query);
    sqlQuery.exec();

    while (sqlQuery.next())
        qDebug() << sqlQuery.value(1).toString() << "is at"
                 << sqlQuery.value(2).toString();
    QVariantList m;
    return m;
}

void MySQLClass::prepareSELECTQuery(QSqlQuery &sqlQuery, Query &query) {
    QString qStr = "SELECT ";
    // Preparing SELECT clause.
    if (query.SELECT.length() != 0) {
        for (const Select &v : query.SELECT) {
            if (v.ColName.length() != 0) qStr += v.ColName;
            else
                throw MySQLError("Column Name can't be empty.");
            if (v.ColAlias.length() != 0) qStr += " AS '" + v.ColAlias + "'";
            qStr += ", ";
        }
        // Removing last `,` from qStr.
        qStr[qStr.length() - 2] = ' ';
    } else
        throw MySQLError("SELECT clause can't be empty.");

    // Preparing FROM cluase.
    if (query.FROM.length() != 0) {
        qStr += "FROM " + query.FROM[0];
    } else
        throw MySQLError("FROM clause can't be empty.");

    // Preparing WHERE clause.
    if (query.WHERE.length() != 0) {
        qStr += " WHERE ";
        for (const Where &v : query.WHERE) qStr += v + " AND ";

        // Removing last `AND` from qStr.
        for (int i = qStr.length() - 4; i <= qStr.length() - 2; ++i)
            qStr[i] = ' ';
    }

    // Preparing GROUP BY clause.
    if (query.GROUP.length() != 0) {
        qStr += " GROUP BY ";
        for (const Group &v : query.GROUP) qStr += v + ", ";

        // Removing last `,` from qStr.
        qStr[qStr.length() - 2] = ' ';
    }

    // Preparing HAVING clause.
    if (query.HAVING.length() != 0) {
        qStr += " HAVING ";
        for (const Having &v : query.HAVING) qStr += v + " AND ";

        // Removing last `AND` from qStr.
        for (int i = qStr.length() - 4; i <= qStr.length() - 2; ++i)
            qStr[i] = ' ';
    }

    // Preparing ORDER BY clause.
    if (query.ORDER.length() != 0) {
        qStr += " ORDER BY ";
        for (const Order &v : query.ORDER)
            if (v.ColName.length() != 0) {
                qStr += v.ColName;
                if (v.Order == ASC) qStr += " ASC";
                else
                    qStr += " DESC";
                qStr += ", ";
            } else
                throw MySQLError("Column Name can't be empty.");

        // Removing last `,` from qStr.
        qStr[qStr.length() - 2] = ' ';
    }

    sqlQuery.prepare(qStr);
    qDebug() << qStr;
}
