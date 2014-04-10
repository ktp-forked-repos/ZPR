#ifndef CONSTS_H
#define CONSTS_H

#include <QColor>
#include <QString>
#include <QHostAddress>

/** Rozmiar planszy. */
const short BOARD_SIZE = 8;

/** Wielkosc pionka w jednostkach logicznych QScene. */
const short PIECE_SIZE  = 30;

/** Liczba pionkow. */
const short PIECE_NUMBER = 12;

/** Kolor ciemnego piona niekliknietego.*/
const QColor BLACK_NORMAL = Qt::red;

/** Kolor ciemnego piona po kliknieciu.*/
const QColor BLACK_FOCUSED = Qt::magenta;

/** Kolor jasnego piona niekliknietego.*/
const QColor WHITE_NORMAL = Qt::white;

/** Kolor jasnego piona po kliknieciu.*/
const QColor WHITE_FOCUSED = Qt::yellow;

/** Wielkosc pola w jednostkach logicznych QScene. */
const int FIELD_SIZE = 30;

/** Kolor pola na ktorym jest dozwolone umieszczenie pionka. */
const QColor CHECKABLE_FIELD_COLOR = Qt::black;

/** Kolor pola na ktorym nie jest dozwolone umieszczenie pionka. */
const QColor NON_CHECKABLE_FIELD_COLOR = Qt::white;

/** Kolor podswietlenia pola podczas wskazywania pola na ktorym pionek ma byl umieszczony. */
const QColor FOCUS_FIELD_COLOR = Qt::yellow;

/** Minimalny numer portu. */
const int MINIMAL_PORT_NUMBER = 1000;

/** Maksymalny numer portu. */
const int MAXIMAL_PORT_NUMBER = 9999;

/** Preferowany port. */
const int PREFFERED_PORT_NUMBER = 7000;

/** Preferowany adres IP. */
const QString PREFFERED_IP_ADDRESS = QHostAddress(QHostAddress::LocalHost).toString();

/** Wyrazenie regularne sprawdzajace czy podany ciag jest prawidlowym adresem IP. */
const QString IP_REG_EXP = "(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";

/** Maksymalna długość komunikatu. */
const int MAX_MOVE_LENGTH = 7;

/** Maksymalna długość komunikatu. */
const char END_MOVE_TOKEN = '.';

#endif // CONSTS_H
