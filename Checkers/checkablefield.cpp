#include "checkablefield.h"
#include <QPainter>
#include <QStyle>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QtDebug>

#include "checkablefield.h"
#include "board.h"
#include "move.h"
#include "consts.h"


CheckableField::CheckableField(short row, short col, Board *board) : Field(row, col)
{
    focused = false;
    blocked = false;

    setAcceptHoverEvents(true);

    connect(this, SIGNAL(move(CheckableField*)), board, SLOT(move(CheckableField*)));
}

void CheckableField::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    if(!focused)
        painter->setBrush(QBrush(CHECKABLE_FIELD_COLOR));
    else
        painter->setBrush(QBrush(FOCUS_FIELD_COLOR));

    painter->setPen(Qt::black);
    painter->drawRect(0, 0, FIELD_SIZE, FIELD_SIZE);
}

void CheckableField::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(blocked) return;
    Piece* actualCheckedPiece = dynamic_cast<Board*>(this->scene())->getPiece();
    if(actualCheckedPiece != NULL && this->childItems().empty() && Move(dynamic_cast<CheckableField*>(actualCheckedPiece->parentItem()), this).isValid())
    {
        focused = true;
        event->setAccepted(true);
        update();
    }
}

void CheckableField::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->setAccepted(true);
    focused = false;
    update();
}

void CheckableField::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(blocked) return;
    emit move(this);
}

Piece * CheckableField::getPiece()
{
    if(!childItems().empty())
        return dynamic_cast<Piece *>(this->childItems().last());
    return NULL;
}

void CheckableField::blockMouseEvents(Piece::COLOR color)
{
    blocked = true;
    if(!childItems().empty())
        dynamic_cast<Piece*>(childItems().at(0))->blockMouseEvents(color);
}

void CheckableField::unblockMouseEvents(Piece::COLOR color)
{
    blocked = false;
    if(!childItems().empty())
        dynamic_cast<Piece*>(childItems().at(0))->unblockMouseEvents(color);
}
