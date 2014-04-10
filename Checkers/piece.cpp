#include <QStyle>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include "piece.h"
#include "board.h"

Piece::Piece(COLOR color, QGraphicsScene* board) : QObject(), QGraphicsItem()
{
    this->color = color;
    this->focused = false;
    mouseEventsBlocked = false;
    if(color == WHITE)
        this->paintColor = WHITE_NORMAL;
    else
        this->paintColor = BLACK_NORMAL;
    if(color == WHITE)
        this->focusedColor = WHITE_FOCUSED;
    else
        this->focusedColor = BLACK_FOCUSED;

    type = MAN;
    connect(this, SIGNAL(pieceChecked(Piece*)), board, SLOT(setCheckedPiece(Piece*)));
}

void Piece::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    if(focused)
        painter->setBrush(QBrush(focusedColor));
    else
        painter->setBrush(QBrush(paintColor));
    painter->setPen(Qt::black);
    painter->drawEllipse(5, 5, 20, 20);
    painter->drawEllipse(7, 7, 16, 16);
    if(type != KING)
        painter->drawEllipse(14, 14, 2, 2);
}

QRectF Piece::boundingRect() const
{
    return QRectF(0, 0, PIECE_SIZE, PIECE_SIZE);
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(mouseEventsBlocked)
        return;
    emit pieceChecked(this);
}

Piece::COLOR Piece::getColor()
{
    return color;
}

void Piece::setColor(COLOR color)
{
    this->color = color;
}

void Piece::setFocused(bool focused)
{
    this->focused = focused;
    update();
}

Piece::TYPE Piece::getType() const
{
    return type;
}

void Piece::makeKing()
{
    type = KING;
    update();
}

void Piece::blockMouseEvents(COLOR color)
{
    if(this->color != color)
        mouseEventsBlocked = true;
}

void Piece::unblockMouseEvents(COLOR color)
{

    if(this->color == color)
        mouseEventsBlocked = false;
}
