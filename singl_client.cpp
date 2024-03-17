#include "singl_client.h"
#include <QObject>
#include <QTcpSocket>

class ServerConnection : public QObject
{
    Q_OBJECT

public:
    static ServerConnection* instance()
    {
        static ServerConnection* connection = new ServerConnection();
        return connection;
    }

    void connectToServer(const QString& ipAddress, int port)
    {
        if (!m_socket->isOpen())
        {
            m_socket->connectToHost(ipAddress, port);
            connect(m_socket, &QTcpSocket::readyRead, this, &ServerConnection::readData);
        }
    }

    void sendData(const QString& data)
    {
        if (m_socket->isOpen())
        {
            m_socket->write(data.toUtf8());
            m_socket->flush();
        }
    }

signals:
    void receivedData(const QString& data);

private slots:
    void readData()
    {
        QString data = QString::fromUtf8(m_socket->readAll());
        emit receivedData(data);
    }

private:
    ServerConnection(QObject* parent = nullptr)
        : QObject(parent), m_socket(new QTcpSocket(this))
    {
    }

    QTcpSocket* m_socket;
};
