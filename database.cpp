#include <database.h>
#include <QCoreApplication>


    Database::~Database() {
        if (m_database.isOpen())
            disconnect();
        if (p_instance)
            delete p_instance;
    }
    Database* Database::getInstance() //Используется для получения единого экземпляра базы данных. Все методы к базе данных выполняются через вызов этого мето
    {
        if (!p_instance)
        {
            p_instance = new Database();
        }
        return p_instance;
    }

    QStringList Database::send_query(QString queryStr) //Отправляет запрос и возвращает список значений, возвращенных запросом типа string. Аргумент: SQL запрос в виде строки
    {
        QSqlQuery query;
        QStringList list;
        query.prepare(queryStr);
        if (!query.exec())
            qDebug() << "Invalid query:" << query.lastError().text();;

        if (!query.isActive()){
            qDebug() << "Invalid query:" <<query.lastError().text();
            return list;
        }

        QSqlRecord rec = query.record();
        while (query.next())
            list.append(query.value(0).toString());
        return list;
    }

    bool Database::connect()
    {
        // Устанавливаем соединение с базой данных
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        m_database.setDatabaseName("../Qt_prom/sql_app.db");
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



