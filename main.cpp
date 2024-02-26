#include <QCoreApplication>
#include "mytcpserver.h"
#include "database.h"


Database* Database::p_instance = 0;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (!Database::getInstance()->connect())
    {
        qDebug() << "Не удалось подключиться к базе данных";
        return -1;
    }
    MyTcpServer myserv;
    return a.exec();
}
