#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() { }

DatabaseManager &DatabaseManager::Instance() {
    static DatabaseManager DatabaseManagerInstance;
    return DatabaseManagerInstance;
}

bool DatabaseManager::Connect(const QString &Host, const QString &DBName,
                              const QString &User, const QString &Password) {
    Database = QSqlDatabase::addDatabase("QMYSQL");
    Database.setHostName(Host);
    Database.setDatabaseName(DBName);
    Database.setUserName(User);
    Database.setPassword(Password);
    return Database.open();
}

void DatabaseManager::Disconnect() {
    if (Database.isOpen()) { Database.close(); }
}

QVariantList DatabaseManager::Select(const QString     &Table,
                                     const QStringList &Columns,
                                     const QVariantMap &Where,
                                     const QString &OrderBy, int Limit,
                                     const QString &GroupBy) {
    QString queryStr =
        QString("SELECT %1 FROM %2").arg(Columns.join(", "), Table);
    QList<QVariant> values;
    queryStr += BuildWhereClause(Where, values);

    if (!GroupBy.isEmpty()) queryStr += " GROUP BY " + GroupBy;

    if (!OrderBy.isEmpty()) queryStr += " ORDER BY " + OrderBy;

    if (Limit > 0) queryStr += QString(" LIMIT %1").arg(Limit);

    QSqlQuery query;
    query.prepare(queryStr);
    for (const QVariant &v : values) query.addBindValue(v);

    QVariantList results;
    if (query.exec()) {
        while (query.next()) {
            QVariantMap row;
            for (int i = 0; i < query.record().count(); ++i)
                row[query.record().fieldName(i)] = query.value(i);
            results.append(row);
        }
    } else {
        qDebug() << "SELECT failed:" << query.lastError().text();
    }

    return results;
}

QString DatabaseManager::BuildWhereClause(const QVariantMap &where,
                                          QList<QVariant>   &values) {
    QStringList clauses;
    for (const QString &key : where.keys()) {
        clauses << QString("%1 = ?").arg(key);
        values << where.value(key);
    }
    return clauses.isEmpty() ? "" : " WHERE " + clauses.join(" AND ");
}
