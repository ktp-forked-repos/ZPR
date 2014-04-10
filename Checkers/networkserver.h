#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QtNetwork>
#include "networkmanager.h"

/**
@brief     Klasa opisujaca serwer.
@details   Zapewnia komunikacje obustronna. Tworzy instancje serwera hostujacego gre.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class NetworkServer : public NetworkManager
{
    Q_OBJECT
private:
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
public:
    /** Konstruktor.*/
    NetworkServer();

public slots:
    /** Metoda uruchamia serwer.
    @param address Adres na ktorym serwer bedzie nasluchiwal polaczenia.
    @param port Port na ktorym serwer bedzie nasluchiwal polaczenia.
    @return "true", gdy ururchomiono, w przeciwnym wypadku "false".*/
    bool startServer(QHostAddress address, int port);

    /** Metoda akceptuje polaczenie. Wylacza serwer i tworzy polaczenie socket.
    @return "true", gdy powiodlo sie, w przeciwnym wypadku "false".*/
    bool acceptConnection();

    /** Wysyla do drugiej strony ruch.
    @param move Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].
    @return "true", gdy wyslano, w przeciwnym wypadku "false".*/
    bool sendMove(QString move);

    /** Odbiera ruch od drugiej strony.
    @return Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].*/
    QString receiveMove();
};

#endif // NETWORKSERVER_H
