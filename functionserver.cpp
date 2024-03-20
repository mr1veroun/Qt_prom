#include "functionserver.h"
#include "QDebug"
#include "database.h"
#include "sha-256.h"

QByteArray parsing(QString data_from_client)//Функция парсинга, получает строку и манипулирует в зависимости от введенной команды.
{
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

QByteArray reg(QString login, QString password)//Функция регистрации, создает новую запись с пользователем в БД. Формат: reg&login&password
{
    std::string sha_password = sha256(password.toStdString());
    password = QString::fromUtf8(sha_password.c_str());
    QString query = QString("INSERT INTO Users ('username', 'password') VALUES ('%1', '%2');").arg(login, password);
    QStringList res = Database::getInstance()->send_query(query, false);
    if (res[0] == "!0!"){
        return "Error during sending query";
    }
    else if (res[0] == "!1!"){
        return login.toUtf8() + " has been signed up";
    }
}
QByteArray auth(QString login, QString password) //Функция авторизации: возвращает success, если пароли в БД и введенный совпадают. Формат: auth&login&password
{
    password.remove("\r\n");
    QString query = QString("SELECT password FROM Users WHERE username = '%1';").arg(login);
    QStringList res = Database::getInstance()->send_query(query, true);
    if (res.length() == 0)
        return "Error";
    std::string sha_password = sha256(password.toStdString());
    password = QString::fromUtf8(sha_password.c_str());
    if (res[0] != password)
        return "Wrong password";
    else
        return "Success";

    }


