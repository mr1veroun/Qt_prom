#ifndef FUNCTIONSERVER_H
#define FUNCTIONSERVER_H
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QLatin1Char>

QByteArray parsing(QString data_from_client);

QByteArray reg(QString login, QString password);

QByteArray auth(QString login, QString password);

#endif // FUNCTIONSERVER_H
