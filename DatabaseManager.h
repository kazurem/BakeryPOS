#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QObject>

class DatabaseManager: public QObject
{
    Q_OBJECT
public:
    DatabaseManager();
    ConnectToDatabase();
    IsConnected();
    CloseConnection();


};

#endif // DATABASEMANAGER_H
