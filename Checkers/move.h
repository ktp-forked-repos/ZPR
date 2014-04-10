#ifndef MOVE_H
#define MOVE_H

#include "board.h"
#include "checkablefield.h"

/**
@brief     Klasa opisujaca ruch na planszy.
@details   Odpowiedzialna za sprawdzenie czy ruch jest poprawny, parsowanie odebranego ruchu z sieci.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class Move
{
private:
    enum DIRECTION{LEFT,RIGHT};
    CheckableField* from;
    CheckableField* to;
    CheckableField* next;
    Piece* checker;
    Piece::COLOR fromColor;
    Piece::TYPE fromType;
    Piece::TYPE nextType;
    Piece::COLOR nextColor;
    DIRECTION direction;
    Board *board;

    short countCheckers(CheckableField *from, CheckableField *to);
public:
    /** Konstruktor klasy
    @param wskaznik do pola z ktorego odbywa sie ruch.
    @param wskaznik do pola na ktore odbywa sie ruch. */
    Move(CheckableField* from, CheckableField* to);

    /** Metoda sprawdzajaca czy ruch jest dozwolony.
    @return czy ruch jest dozwolony */
    bool isValid();

    /** Zwraca wskaznik na pionek ktory zostal w tym ruchu zbity.
    @return wskaznik na pionek ktory zostal w tym ruchu zbity. */
    Piece* getChecker();

    /** Metoda statyczna do wykonania ruchu przychodzacego z sieci.
    @param move Ruch w postaci R1C1R2C2R3C3. [1-skad, 2-dokad, 3-opcjonalnie, co zbite, .-znak konca].
    @param *scene wskaznik na scene (klase nadrzedna planszy). */
    static bool doMove(QString move, QGraphicsScene *scene);

    /** Metoda zwracajaca czy po tym ruchu jest mozliwe jeszcze zbicie.
    @return czy po tym ruchu jest mozliwe jeszcze zbicie. */
    bool isAnotherMove();
};

#endif // MOVE_H
