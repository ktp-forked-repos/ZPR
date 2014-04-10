#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsItem>
/**
@brief     Klasa opisujaca pojedynczy pionek.
@details   Definiuje metody zmiany stanow, kolorow, blokuje lub odblokowuje klikniecia.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class Piece : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    /** Definiuje, czy dany kamien jest pionem czy damka. */
    enum TYPE{MAN, KING};

    /** Definiuje, czy dany kamien jest "czarny" czy "bialy". */
    enum COLOR{WHITE, BLACK};
private:
    QColor paintColor;
    QColor focusedColor;
    bool focused;
    TYPE type;
    COLOR color;
    bool mouseEventsBlocked;
public:
    /** Konstruktor.
    @param *parent Wskaznik na rodzica.*/
    explicit Piece(QObject *parent = 0);

    /** Konstruktor.
    @param color Definiuje czy tworzony obiekt jest "czarny" czy "bialy".
    @param *board Wskaznik na plansze.*/
    Piece(COLOR color, QGraphicsScene *board);

    /** Tworzy prostokat okalajacy obiekt.
    @return Zwraca prostokat okalajacy pojedyncze pole. */
    QRectF boundingRect() const;

    /** Rysuje odpowiednio obiekt.
    @param *painter Niejawny malarz.
    @param *option
    @param *widget*/
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    /** Pobiera kolor danego piona lub danej damki.
    @return Kolor kamienia. */
    COLOR getColor();

    /** Pobiera typ kamienia definiujacego, czy jest damka czy pionem.
    @return Typ kamienia. */
    TYPE getType() const;

    /** Ustala kolor kamienia
    @param color Kolor kamienia (BLACK / WHITE).*/
    void setColor(COLOR color);

    /** Ustala czy obiekt jest zaznaczony, czy nie.
    @param focused "true" dla zaznaczony, "false" w przeciwnym razie.*/
    void setFocused(bool focused);

    /** Zamienia pionek w damke.*/
    void makeKing();

    /** Blokuje klikniecia dla danego koloru.
    @param color Kolor, ktorego klikniecia maja byc zablokowane.*/
    void blockMouseEvents(COLOR color);

    /** Odblokowuje klikniecia dla danego koloru.
    @param color Kolor, ktorego klikniecia maja byc zablokowane.*/
    void unblockMouseEvents(COLOR color);

protected:
    /** Metoda obslugi klikniecia.
    @param *event Wskaznik na zdarzenie.*/
    void mousePressEvent( QGraphicsSceneMouseEvent * event );
signals:
    void pieceChecked(Piece* piece);

};

#endif // PIECE_H
