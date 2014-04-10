#include <QPainter>
#include <QStyle>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QtDebug>

#include "field.h"
#include "board.h"
#include "move.h"
#include "consts.h"

Field::Field(short row, short col) :
    QGraphicsItem()
{
    this->row = row;
    this->col = col;
}

QRectF Field::boundingRect() const
{
    return QRectF(0, 0, FIELD_SIZE, FIELD_SIZE);
}

void Field::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
}

void Field::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
}

void Field::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
}

void Field::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

short Field::getRow() const
{
    return row;
}

short Field::getCol() const
{
    return col;
}
