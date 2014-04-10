#include "uncheckablefield.h"
#include "consts.h"
#include <QPainter>

UncheckableField::UncheckableField(short row, short col) : Field(row, col){}

void UncheckableField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(NON_CHECKABLE_FIELD_COLOR));
    painter->setPen(Qt::black);
    painter->drawRect(0, 0, FIELD_SIZE, FIELD_SIZE);
}
