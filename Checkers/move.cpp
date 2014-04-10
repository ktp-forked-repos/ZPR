#include <QDebug>
#include <iostream>

#include "move.h"
#include "board.h"

Move::Move(CheckableField* from, CheckableField* to)
{
    this->from = from;
    this->to = to;
    checker = NULL;
    fromColor = from->getPiece()->getColor();
    fromType = from->getPiece()->getType();
    direction = from->getCol() - to->getCol() > 0 ? LEFT : RIGHT;

    board = dynamic_cast<Board*>(from->scene());

    if(from->getPiece()->getType() != Piece::KING)
    {
        if(from->getCol() != to->getCol() && from->getRow() != to->getRow())
        {
            next = NULL;
            if(direction == LEFT)
            {
                if(from->getPiece()->getColor() == Piece::WHITE)
                    next = board->getFieldAt(from->getRow() - 1, from->getCol() - 1);
                else
                    next = board->getFieldAt(from->getRow() + 1, from->getCol() - 1);
            }
            else
            {
                if(from->getPiece()->getColor() == Piece::WHITE)
                    next = board->getFieldAt(from->getRow() - 1, from->getCol() + 1);
                else
                    next = board->getFieldAt(from->getRow() + 1, from->getCol() + 1);
            }

            if(next->getPiece() != NULL)
            {
                nextType = next->getPiece()->getType();
                nextColor = next->getPiece()->getColor();
            }
        }
    }
}

bool Move::isValid()
{
    if(to == NULL)
        return false;

    if(to->getPiece() != NULL)
        return false;

    if(from->getCol() == to->getCol() && from->getRow() == to->getRow())
        return false;

    short columnDiff = from->getCol() - to->getCol();
    short rowDiff = from->getRow() - to->getRow();

    if(abs(columnDiff) == 1 && rowDiff == 1 && fromColor == Piece::WHITE)
        return true;
    else if(abs(columnDiff) == 2 && rowDiff == 2 && fromColor == Piece::WHITE && nextColor == Piece::BLACK)
    {
        checker = next->getPiece();
        return true;
    }

    if(abs(columnDiff) == 1 && rowDiff == -1 && fromColor == Piece::BLACK)
        return true;
    else if(abs(columnDiff) == 2 && rowDiff == -2 && fromColor == Piece::BLACK && nextColor == Piece::WHITE)
    {
        checker = next->getPiece();
        return true;
    }

    //KINGS
    if(fromType == Piece::KING && abs(columnDiff) == abs(rowDiff))
    {
        short countOfCheckers;
        if(from->getRow() < to->getRow())
            countOfCheckers = countCheckers(from, to);
        else
            countOfCheckers = countCheckers(to, from);

        if(countOfCheckers == 0)
        {
            checker = NULL;
            return true;
        }
        if(countOfCheckers == 1)
        {
            CheckableField* f = dynamic_cast<CheckableField*>(checker->parentItem());
            if(abs(f->getCol()-to->getCol()) == 1 && abs(f->getRow()-to->getRow()) == 1 && checker->getColor() != fromColor)
                return true;
        }
        return false;
    }

    return false;
}

Piece * Move::getChecker()
{
    return checker;
}

/**
  Liczba przeskakiwanych pol
  */
short Move::countCheckers(CheckableField* from, CheckableField* to)
{
    short count = 0;

    Board* board = dynamic_cast<Board*>(from->scene());

    direction = from->getCol() - to->getCol() > 0 ? LEFT : RIGHT;

    int row, col;
    for(row = from->getRow()+1, direction == RIGHT ? col = from->getCol()+1 : col = from->getCol()-1; row < to->getRow(), direction == RIGHT ? col < to->getCol() : col > to->getCol(); row++, direction == RIGHT ? col++ : col--)
    {
        if(board->getFieldAt(row, col)->getPiece() != NULL)
        {
            count++;
            if(checker == NULL)
                checker = board->getFieldAt(row, col)->getPiece();
        }
    }
    return count;
}

bool Move::doMove(QString move, QGraphicsScene *scene)
{
    int fromRow, fromCol, toRow, toCol;
    fromRow = move.at(0).digitValue();
    fromCol = move.at(1).digitValue();
    toRow = move.at(2).digitValue();
    toCol = move.at(3).digitValue();

    Board *board = dynamic_cast<Board*>(scene);
    Piece *fromPiece = board->getFieldAt(fromRow, fromCol)->getPiece();
    fromPiece->setParentItem(board->getFieldAt(toRow, toCol));

    if(move.size() == MAX_MOVE_LENGTH || move.size() == MAX_MOVE_LENGTH - 1)
    {
        int removeRow = move.at(4).digitValue();
        int removeCol = move.at(5).digitValue();

        Piece *removePiece = board->getFieldAt(removeRow, removeCol)->getPiece();
        scene->removeItem(removePiece);
    }

    if(toRow == 0 || toRow == 7)
        board->getFieldAt(toRow, toCol)->getPiece()->makeKing();

    board->update();

    return move[move.size() - 1] == END_MOVE_TOKEN;
}

bool Move::isAnotherMove()
{
    Move *m1 = NULL, *m2 = NULL;
    CheckableField *field;

    short fromRow = to->getRow();
    short fromCol = to->getCol();

    if(checker == NULL || this->fromType == Piece::KING)
        return false;

    if(this->fromColor == Piece::WHITE) //do gory
    {
        field = board->getFieldAt(fromRow - 2, fromCol - 2);
        if(field != NULL)
            m1 = new Move(to, field);

        field = board->getFieldAt(fromRow - 2, fromCol + 2);
        if(field != NULL)
            m2 = new Move(to, field);

    }
    else //na dol
    {
        field = board->getFieldAt(fromRow + 2, fromCol - 2);
        if(field != NULL)
            m1 = new Move(to, field);

        field = board->getFieldAt(fromRow + 2, fromCol + 2);
        if(field != NULL)
            m2 = new Move(to, field);
    }

    if(m1 != NULL && m1->isValid())//tricky
        return true;

    if(m2 != NULL && m2->isValid())//tricky
        return true;

    delete m1;
    delete m2;

    return false;
}

