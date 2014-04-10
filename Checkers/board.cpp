#include <QDebug>
#include <iostream>

#include "board.h"
#include "piece.h"
#include "checkablefield.h"
#include "uncheckablefield.h"
#include "move.h"


Board::Board(MainWindow* mWnd)
{
    for(int i = 0; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            if((i+j)%2 != 0)
                addItem(new CheckableField(j, i, this));
            else
                addItem(new UncheckableField(j, i));
            items().front()->setPos(i*PIECE_SIZE, j*PIECE_SIZE);
            fields[j][i] = dynamic_cast<Field*>(items().front());
        }
    }

    for(int i = 0; i < BOARD_SIZE; ++i)
    {
        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            if((i+j)%2 != 0 && j != 3 && j != 4)
            {
                Piece* newPiece = new Piece(j > 4 ? Piece::WHITE : Piece::BLACK, this);
                newPiece->setParentItem(fields[j][i]);
            }
        }
    }

    checkedPiece = NULL;
    gamerColor = Piece::BLACK;
    blockMoves();
    gamerColor = Piece::WHITE;
    blockMoves();

    connect(this, SIGNAL(whiteInc(bool)), mWnd, SLOT(whitePointsInc(bool)));
    connect(this, SIGNAL(blackInc(bool)), mWnd, SLOT(blackPointsInc(bool)));

    connect(this, SIGNAL(move(QString)), mWnd, SLOT(sendMove(QString)));
}

void Board::setCheckedPiece(Piece *piece)
{
    if(checkedPiece)
        checkedPiece->setFocused(false);

    checkedPiece = piece;

    if(checkedPiece)
        checkedPiece->setFocused(true);

}

Piece * Board::getPiece()
{
    return checkedPiece;
}

CheckableField * Board::getFieldAt(short row, short col)
{
    if(row < 0 || row > BOARD_SIZE - 1 || col < 0 || col > BOARD_SIZE - 1)
        return NULL;
    return dynamic_cast<CheckableField*>(fields[row][col]);
}

void Board::blockMoves()
{
    this->setForegroundBrush(QBrush(QColor(100,100,100,100)));

    foreach(QGraphicsItem *item, items())
    {
        if(dynamic_cast<CheckableField*>(item))
            dynamic_cast<CheckableField*>(item)->blockMouseEvents(gamerColor);
    }
}

void Board::unblockMoves()
{
    this->setForegroundBrush(Qt::NoBrush);
    foreach(QGraphicsItem * item, items())
    {
        if(dynamic_cast<CheckableField*>(item))
            dynamic_cast<CheckableField*>(item)->unblockMouseEvents(gamerColor);
    }
}

void Board::blockPiecesMoves(Piece *piece)
{
    foreach(QGraphicsItem *item, items())
    {
        if(dynamic_cast<Piece*>(item))
        {
            if(piece != dynamic_cast<Piece*>(item))
                dynamic_cast<Piece*>(item)->blockMouseEvents(gamerColor == Piece::WHITE ? Piece::BLACK : Piece::WHITE);
        }
    }
}

void Board::setGamerColor(Piece::COLOR color)
{
    gamerColor = color;
}

void Board::move(CheckableField *field)
{
    Piece* actualCheckedPiece = this->getPiece();
    if(actualCheckedPiece != NULL)
    {
        CheckableField* parentOfActualCheckedPiece = dynamic_cast<CheckableField*>(actualCheckedPiece->parentItem());
        Move m(parentOfActualCheckedPiece, field);
        if(m.isValid())
        {

            //utworzenie ruchu
            QString moveString;
            moveString.append(QString::number(parentOfActualCheckedPiece->getRow()));
            moveString.append(QString::number(parentOfActualCheckedPiece->getCol()));
            moveString.append(QString::number(field->getRow()));
            moveString.append(QString::number(field->getCol()));


            actualCheckedPiece->setParentItem(field);
            if(field->getRow() == 0 || field->getRow() == 7)
            {
                actualCheckedPiece->makeKing();
                actualCheckedPiece->setFocused(false);
            }
            Piece* checkerToRemove = m.getChecker();
            if(checkerToRemove != NULL)
            {
                //if jest do zbicia to tez go wyslij
                CheckableField* checkerToRemoveField = dynamic_cast<CheckableField *>(checkerToRemove->parentItem());
                moveString.append(QString::number(checkerToRemoveField->getRow()));
                moveString.append(QString::number(checkerToRemoveField->getCol()));

                if(m.getChecker()->getColor()==Piece::WHITE)
                    emit blackInc(false);
                else
                    emit whiteInc(false);
                this->removeItem(checkerToRemove);
            }

            if(m.isAnotherMove())
            {
                emit move(moveString);
                blockPiecesMoves(actualCheckedPiece);
            }
            else
            {
                moveString.append(END_MOVE_TOKEN);
                emit move(moveString);
                actualCheckedPiece->setFocused(false);
                this->setCheckedPiece(NULL);
                this->blockMoves();
            }

        }
    }
}
