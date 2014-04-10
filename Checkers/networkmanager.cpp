#include <QMessageBox>

#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent)
{
}

void NetworkManager::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::information(0, tr("Checkers"),
                                 tr("Polaczenie przerwane. "));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(0, tr("Checkers"),
                                 tr("Nie znaleziono hosta. "
                                    "Sprawdz podany adres i port."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(0, tr("Checkers"),
                                 tr("Polaczenie przerwane. "
                                    "Upewnij sie, ze serwer dziala, "
                                    "oraz czy podany adres oraz port "
                                    "sa prawidlowe."));
        break;
    default:
        QMessageBox::information(0, tr("Checkers"),
                                 tr("Wystapil blad: %1.")
                                 .arg(socketError));
    }
}

