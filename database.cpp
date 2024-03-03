#include <database.h>


    Database::~Database() {
        if (m_database.isOpen())
            disconnect();
        if (p_instance)
            delete p_instance;
    }
    Database* Database::getInstance(){
        if (!p_instance)
        {
            p_instance = new Database();
        }
        return p_instance;
    }

    QSqlQuery Database::send_query(QString queryStr)
    {
        QSqlQuery query;
        query.prepare(queryStr);
        if (!query.exec())
            qDebug() << "Invalid query:" << query.lastError().text();;
        return query;
    }

    bool Database::connect()
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

    void Database::disconnect()
    {
        // Отключаемся от базы данных
        m_database.close();
    }



