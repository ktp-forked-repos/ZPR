#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsItem>

/**
@brief     Klasa pojedynczego pola planszy.
@details   Zapewnia metody rysowania i obslugi zdarzen na polu.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class Field : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    short row;
    short col;
public:
    /** Konstruktor.
    @param row Numer rzedu.
    @param col Numer kolumny. */
    explicit Field(short row, short col);

    /** Tworzy prostokat okalajacy obiekt.
    @return Zwraca prostokat okalajacy pojedyncze pole. */
    QRectF boundingRect() const;

    /** Rysuje odpowiednio niezaznaczalne jasne pole..
    @param *painter Niejawny malarz.
    @param *option
    @param *widget*/
    virtual void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 ) = 0;

    /** Pobiera numer rzedu.
    @return Numer rzedu [0-BOARD_SIZE].*/
    short getRow() const;

    /** Pobiera numer kolumny.
    @return Numer kolumny [0-BOARD_SIZE].*/
    short getCol() const;

protected:
    /** Obsluga wydarzenia: najazd na pole.
    @param *event Wskaznik na event.*/
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    /** Obsluga wydarzenia: opuszczenie pola.
    @param *event Wskaznik na event.*/
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    /** Obsluga wydarzenia: klikniecie na pole.
    @param *event Wskaznik na event.*/
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // FIELD_H
