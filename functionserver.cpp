#include "functionserver.h"
#include "QDebug"
#include "database.h"


QByteArray parsing(QString data_from_client){
    QStringList clue_words = data_from_client.split(QLatin1Char('&'));
    QString action_type = clue_words.front();
    if (clue_words.length() != 3)
        return "invalid input\r\n";
    clue_words.pop_front();
    QByteArray res;
    if (action_type == "auth"){
        res = auth(clue_words.at(0), clue_words.at(1));
    }
    else if (action_type == "reg"){
        res = reg(clue_words.at(0), clue_words.at(1));
    }
    else{
        res = "There is no such a function";
    }
    res += "\r\n";
    return res;

}

QByteArray reg(QString login, QString password){
    QString query = QString("INSERT INTO Users ('username', 'password') VALUES (%1, %2);").arg(login, password);
    Database::getInstance()->send_query(query);
    return login.toUtf8() + " has been signed up";
}
QByteArray auth(QString login, QString password){
    password.remove("\r\n");
    QString query = QString("SELECT password FROM Users WHERE username = '%1';").arg(login);
    QSqlQuery res = Database::getInstance()->send_query(query);
    if (!res.isActive()){
        qDebug() << "Invalid query:" << res.lastError().text();
        return "";
    }

    QSqlRecord rec = res.record();
    qDebug() << rec.indexOf("password");
    QString opassword = "";
    while (res.next())
        opassword = res.value(rec.indexOf("password")).toString();
    qDebug() << opassword << " " << password;
    if (opassword != password)
        return "Wrong password";
    else
        return "Success";



    }


