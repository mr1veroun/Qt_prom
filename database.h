#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

class Database
{

private:

    static Database * p_instance;
    QSqlDatabase m_database;
protected:


protected:
    Database(){}
    Database(const Database& );
    Database& operator = (Database&);
    ~Database() {
        if (m_database.isOpen())
            disconnect();
        if (p_instance)
            delete p_instance;
    }

public:


    static Database* getInstance(){
        if (!p_instance)
        {
            p_instance = new Database();
        }
        return p_instance;
    }

    QSqlQuery send_query(QString queryStr)
    {
        QSqlQuery query;
        query.prepare(queryStr);
        if (!query.exec())
            qDebug() << "Invalid query:" << query.lastError().text();;
        return query;
    }
    bool connect()
    {
        // Устанавливаем соединение с базой данных
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        m_database.setDatabaseName("C:/Users/Magras/Documents/Qt_prom/sql_app.db");
        if (!m_database.open())
        {
            qDebug() << "Ошибка соединения с базой данных";
            return false;
        }

        return true;
    }

    void disconnect()
    {
        // Отключаемся от базы данных
        m_database.close();
    }


};


#endif // DATABASE_H
