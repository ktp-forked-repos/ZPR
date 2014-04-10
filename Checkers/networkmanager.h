#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QtNetwork>

/**
@brief     Klasa opisujaca menadzer sieciowy.
@details   Zapewnia komunikacje klienta i serwera.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class NetworkManager : public QObject
{
    Q_OBJECT
public:
    /** Konstruktor menadzera sieciowego.
    @param *parent Wskaznik na rodzica.*/
    explicit NetworkManager(QObject *parent = 0);
    
signals:
    /** Odebrano ruch od drugiej strony.
    @param move Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].*/
    virtual void receivedMove(QString move);

public slots:
    /** Wysyla do drugiej strony ruch.
    @param move Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].
    @return "true", gdy wyslano, w przeciwnym wypadku "false".*/
    virtual bool sendMove(QString move) = 0;

    /** Odbiera ruch od drugiej strony.
    @return Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].*/
    virtual QString receiveMove() = 0;

    /** Wyswietla bledy polaczenia.
    @param socketError Typ bledu.*/
    void displayError(QAbstractSocket::SocketError socketError);
    
};

#endif // NETWORKMANAGER_H
