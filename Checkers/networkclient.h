#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QtNetwork>

#include "networkmanager.h"

/**
@brief     Klasa opisujaca klienta.
@details   Zapewnia komunikacje obustronna. Tworzy instancje dolaczanego klienta.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class NetworkClient : public NetworkManager
{
    Q_OBJECT
public:
    /** Konstruktor.*/
    NetworkClient();

public slots:
    /** Podlacza klienta do serwera.
    @param address Adres serwera.
    @param port Port serwera.
    @return "true", gdy podlaczono, w przeciwnym wypadku "false".*/
    bool connectTo(QHostAddress address, int port);

    /** Wysyla do drugiej strony ruch.
    @param move Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].
    @return "true", gdy wyslano, w przeciwnym wypadku "false".*/
    bool sendMove(QString move);

    /** Odbiera ruch od drugiej strony.
    @return Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].*/
    QString receiveMove();
private:
    QTcpSocket tcpClient;
};

#endif // NETWORKCLIENT_H
