#include "networkserver.h"
#include "qdebug.h"

NetworkServer::NetworkServer()
{
    connect(&tcpServer,SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    tcpServerConnection = NULL;
}

bool NetworkServer::startServer(QHostAddress address, int port)
{
    bool result = false;
    tcpServer.setMaxPendingConnections(1);
    result = tcpServer.listen(address, port);
    return result;
}

bool NetworkServer::acceptConnection()
{
    bool result = false;
    tcpServerConnection = tcpServer.nextPendingConnection();
    tcpServer.close();

    result = connect(tcpServerConnection, SIGNAL(readyRead()), this, SLOT(receiveMove()));

    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
                 this, SLOT(displayError(QAbstractSocket::SocketError)));

    return result;
}

bool NetworkServer::sendMove(QString move)
{
    QByteArray block;
    QDataStream outPutDataStream(&block, QIODevice::WriteOnly);

    outPutDataStream << move;
    tcpServerConnection->write(block);
    return tcpServerConnection->flush();
}

QString NetworkServer::receiveMove()
{
    QDataStream incomingDataStream(tcpServerConnection);
    tcpServerConnection->flush();
    QString move;
    incomingDataStream >> move;
    emit receivedMove(move);
    return move;
}

