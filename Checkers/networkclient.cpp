#include "networkclient.h"
#include "qdebug.h"

NetworkClient::NetworkClient()
{
    connect(&tcpClient,SIGNAL(readyRead()), this, SLOT(receiveMove()));
}

bool NetworkClient::connectTo(QHostAddress address, int port)
{
    bool result;
    tcpClient.connectToHost(address, port);
    result = tcpClient.state() != QAbstractSocket::UnconnectedState;

    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    return result;
}

bool NetworkClient::sendMove(QString move)
{
    QByteArray block;
    QDataStream outPutDataStream(&block, QIODevice::WriteOnly);

    outPutDataStream << move;

      tcpClient.write(block);
      return tcpClient.flush();
}

QString NetworkClient::receiveMove()
{
    QDataStream incomingDataStream(&tcpClient);
    tcpClient.flush();

    QString move;
    incomingDataStream >> move;
    emit receivedMove(move);
    return move;
}
