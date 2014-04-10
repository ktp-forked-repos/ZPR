#ifndef UNCHECKABLEFIELD_H
#define UNCHECKABLEFIELD_H

#include "field.h"

/**
@brief     Klasa wywoluje malowanie niezaznaczalnego jasnego pola.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class UncheckableField : public Field
{
public:
    UncheckableField(short row, short col);

public:
    /** Rysuje odpowiednio niezaznaczalne jasne pole..
    @param *painter Niejawny malarz.
    @param *option
    @param *widget*/
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
};

#endif // UNCHECKABLEFIELD_H
