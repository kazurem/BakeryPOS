#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class DatabaseManager {
  public:
    static DatabaseManager &Instance();

    bool Connect(const QString &Host, const QString &DBName,
                 const QString &User, const QString &Password);
    void Disconnect();

    QVariantList Select(const QString &Table, const QStringList &Columns,
                        const QVariantMap &Where, const QString &OrderBy,
                        int Limit, const QString &GroupBy);

    QString BuildWhereClause(const QVariantMap &where, QList<QVariant> &values);

  private:
    DatabaseManager();

    DatabaseManager(const DatabaseManager &)            = delete;
    DatabaseManager &operator=(const DatabaseManager &) = delete;

    QSqlDatabase Database;
};

#endif // DATABASEMANAGER_H
