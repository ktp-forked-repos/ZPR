#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>

#include "mainwindow.h"
#include "field.h"
#include "piece.h"
#include "consts.h"
#include "checkablefield.h"

class CheckableField;

/**
@brief     Klasa opisujaca plansze.
@details   Odpowiedzialna za przechowywanie pionkow, pol, relacji miedzy nimi.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class Board : public QGraphicsScene
{
    Q_OBJECT
private:
    Piece* checkedPiece;
    Field* fields[BOARD_SIZE][BOARD_SIZE];
    Piece::COLOR gamerColor;
    QString bufferedFrom;
    QString bufferedTo;
    QString bufferedMove;
public:
    /** Konstruktor klasy.
    @param *mWnd wskazanie do glownego okna. */
    explicit Board(MainWindow *mWnd);

    /** Pobiera aktualnie zaznaczony pionek.
    @return wskaznik na aktualnie zaznaczony pionek. */
    Piece* getPiece();

    /** Pobiera wskaznik na pole o podanym wspolrzednych.
    @param row rzad pobieranego pola.
    @param col kolumna pobieranego pola.
    @return wskaznik na pole o podanym wspolrzednych. */
    CheckableField *getFieldAt(short row, short col);

    /** Blokuje ruchy na planszy. */
    void blockMoves();

    /** Odblokowuje ruchy na planszy. */
    void unblockMoves();

    /** Ustawia kolor pionkow gracza.
    @param color kolor pionkow. */
    void setGamerColor(Piece::COLOR color);

    /** Blokuje ruchy pionkow na planszy po za wyznaczonym.
    @param *piece wskaznik do pola ktore ma nie byc blokowane. */
    void blockPiecesMoves(Piece *piece);
signals:
    /** Sygnal wysylany gdy zbity "bialy" pionek. */
    void whiteInc(bool ifTest);

    /** Sygnal wysylany gdy zbity "czarny" pionek. */
    void blackInc(bool ifTest);

    /** Sygnal wysylany gdy zbity "czarny" pionek.
    @param move Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca]. */
    void move(QString move);

public slots:
    /** Ustawia aktualnie zaznaczony pionek.
    @param move wskaznik na aktualnie zaznaczony pionek. */
    void setCheckedPiece(Piece* piece);

    /** Wykonuje operacje ruchu na wskazane pole.
    @param move wskaznik do pola na ktore zostanie wykonany ruch. */
    void move(CheckableField *field);
};

#endif // BOARD_H
