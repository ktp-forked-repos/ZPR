#ifndef CHECKABLEFIELD_H
#define CHECKABLEFIELD_H

#include "field.h"
#include "checkablefield.h"
#include "piece.h"
#include "board.h"

class Board;

/**
@brief Klasa opisujaca pole na ktore mozna wykonywac ruchy.
@details   Odpowiedzialna za przechowywanie pionkow, pol, relacji miedzy nimi.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak */
class CheckableField : public Field
{
    Q_OBJECT

private:
    bool focused;
    bool blocked;

public:
    /** Konstruktor klasy.
    @param row rzad tworzonego pola.
    @param col kolumna tworzonego pola.
    @param wskaznik na plansze. */
    explicit CheckableField(short row, short col, Board *board);

    /** Rysuje obiekt
    @param *painter Niejawny malarz.
    @param *option
    @param *widget*/
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    /** Zwraca pionek ustawiony na tym polu lub NULL jesli jest puste.
      @return wskaznik pionka ustawionego na tym polu*/
    Piece* getPiece();

    /** Blokuje zdarzenia myszy na tym polu
    @param color kolor pionka */
    void blockMouseEvents(Piece::COLOR color);

    /** Odblokowuje zdarzenia myszy na tym polu
    @param color kolor pionka */
    void unblockMouseEvents(Piece::COLOR color);

protected:
    /** Obsluga wydarzenia: najazd na pole.
    @param *event Wskaznik na event.*/
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    /** Obsluga wydarzenia: opuszczenie pola.
    @param *event Wskaznik na event.*/
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    /** Obsluga wydarzenia: klikniecie na pole.
    @param *event Wskaznik na event.*/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    /** Sygnal wysylany gdy zbity "bialy" pionek. */
    void whiteInc();

    /** Sygnal wysylany gdy zbity "czarny" pionek. */
    void blackInc();

    /** Wykonuje operacje ruchu na wskazane pole.
    @param move wskaznik do pola na ktore zostanie wykonany ruch. */
    void move(CheckableField * field);
};

#endif // CHECKABLEFIELD_H
