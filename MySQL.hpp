#ifndef _MYSQL_HPP
#define _MYSQL_HPP

#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

enum OrderBy { ASC = 0, DESC = 1 };

class MySQLClass {
  private:
    struct Select {
        QString ColName  = "";
        QString ColAlias = "";
    };

    // typedef's to make Interface consistent
    typedef QString From;
    typedef QString Where;
    typedef QString Group;
    typedef QString Having;

    struct Order {
        QString     ColName = "";
        OrderBy     Order   = ASC;
    };

    // All parts of a Query.
    struct Query {
        QList<Select> SELECT = {};
        QList<From>   FROM   = {};
        QList<Where>  WHERE  = {};
        QList<Group>  GROUP  = {};
        QList<Having> HAVING = {};
        QList<Order>  ORDER  = {};
    };

    QSqlDatabase MySQLconn;

    void prepareSELECTQuery(QSqlQuery &sqlQuery, Query &query);
    void prepareSELECTClause();

  protected:
    bool Connect(const QString &Host, const QString &DBName,
                 const QString &user, const QString &passwd);

  public:
    MySQLClass();

    class MySQLError {
      private:
        QString errStr;

      public:
        QString what() const { return this->errStr; }
        MySQLError(const QString errStr) { this->errStr = errStr; }
    };
    QVariantList SELECT(Query query);
};

class MySQLadmin : public MySQLClass {
  private:
  protected:
  public:
};

class MySQLusers : public MySQLClass {
  private:
  protected:
  public:
};

#endif
