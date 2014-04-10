#include <QMessageBox>
#include <iostream>

#include "tests.h"
#include "piece.h"
#include "board.h"
#include "move.h"
#include "consts.h"
#include "networkserver.h"
#include "networkclient.h"

Tests::Tests()
{}

bool Tests::runTests(Board *board)
{
    bool result = false;
    //needs to be written like this to call test functions twice
    if(CheckersTests(board))
        result = true;
    if(!NetworkTests())
        result = false;
    return result;
}

bool Tests::CheckersTests(Board *board)
{
    bool result = false;
    short passed=0, all=0;
    std::cout << "# Checkers tests:" << std::endl;
    passed += (CTManMove(board) ? 1 : 0); all++;
    passed += (CTKingMove(board) ? 1 : 0); all++;
    passed += (CTManCaptures(board) ? 1 : 0); all++;
    passed += (CTKingCaptures(board) ? 1 : 0); all++;
    passed += (CTMakeKing(board) ? 1 : 0); all++;
    passed += (CTWhiteWins(true) ? 1 : 0); all++;
    passed += (CTBlackWins(true) ? 1 : 0); all++;
    std::cout << passed << "/" << all << " PASSED!" << std::endl;
    if(passed == all)
        result = true;
    return result;
}

bool Tests::CTManMove(Board *board)
{
    bool result = true;
    int tmp = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j+=2){
            tmp =j + (i%2 ? 0 : 1);
            Move testMove(board->getFieldAt(5,4),board->getFieldAt(i,tmp));
            if(testMove.isValid()){
                if(!(i==4 && tmp==3))
                    if(!(i==4 && tmp==5)){
                        result=false;
                    }
            }
            else
                if(i==4 && tmp==3)
                    result=false;
                else
                    if(i==4 && tmp==5){
                        result=false;
                    }
        }
    std::cout << "CTManMove: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::CTKingMove(Board *board)
{
    bool result = true;
    board->getFieldAt(5,4)->getPiece()->makeKing();
    int tmp = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j+=2){
            tmp =j + (i%2 ? 0 : 1);
            Move testMove(board->getFieldAt(5,4),board->getFieldAt(i,tmp));
            if(testMove.isValid()){
                if(!(i==3 && tmp==2))
                    if(!(i==3 && tmp==6))
                        if(!(i==4 && tmp==3))
                            if(!(i==4 && tmp==5))
                                result=false;
            }
            else
                if(i==4 && tmp==3)
                    result=false;
                else
                    if(i==4 && tmp==5)
                        result=false;
                    else
                        if(i==3 && tmp==2)
                            result=false;
                        else
                            if(i==3 && tmp==6)
                                result=false;
        }

    std::cout << "CTKingMove: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::CTManCaptures(Board *board)
{
    bool result = false;

    board->getFieldAt(2,1)->getPiece()->setParentItem(board->getFieldAt(3,2));
    board->getFieldAt(3,2)->getPiece()->setParentItem(board->getFieldAt(4,3));
    if(Move(board->getFieldAt(5,4),  board->getFieldAt(3,2)).isValid())
    {
        board->getFieldAt(5,0)->getPiece()->setParentItem(board->getFieldAt(4,1));
        if(!Move(board->getFieldAt(5,2),  board->getFieldAt(3,0)).isValid())
            result=true;
    }

    std::cout << "CTManCaptures: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::CTKingCaptures(Board *board)
{
    bool result = false;

    if(!Move(board->getFieldAt(5,4),  board->getFieldAt(2,1)).isValid())
        if(Move(board->getFieldAt(5,4),  board->getFieldAt(3,2)).isValid())
            result = true;

    std::cout << "CTKingCaptures: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::CTMakeKing(Board *board)
{
    bool result = false;
    Piece testPiece(Piece::BLACK, board);
    if(testPiece.getType() == Piece::MAN){
        testPiece.makeKing(); //tries to make man a king
        if(testPiece.getType() == Piece::KING){
            testPiece.makeKing(); //tries to make king a king
            if(testPiece.getType() == Piece::KING)
                result = true;
        }
    }
    std::cout << "CTMakeKing: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::CTWhiteWins(bool ifTest)
{
    bool result = false;
    MainWindow mw(0);
    for(int i=0;i<PIECE_NUMBER;i++)
        result = mw.whitePointsInc(ifTest);
    std::cout << "CTWin: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::CTBlackWins(bool ifTest)
{
    bool result = false;
    MainWindow mw(0);
    for(int i=0;i<PIECE_NUMBER;i++){
        result = mw.blackPointsInc(ifTest);
    }
    std::cout << "CTLoss: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::NTStartServer(NetworkManager *ns, short port)
{
    bool result = false;
    QHostAddress testAddress = QHostAddress::LocalHost;

    result = dynamic_cast<NetworkServer*>(ns)->startServer(testAddress, port);
    std::cout << "NTStartServer: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::NTConnectClient(NetworkManager *nc, short port)
{
    bool result = false;

    if(dynamic_cast<NetworkClient*>(nc)->connectTo(QHostAddress::LocalHost, port)) //IP OK port OK
        result=true;

    std::cout << "NTConnectClient: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::NTClientSends(NetworkManager *nc)
{
    bool result = false;
    if(dynamic_cast<NetworkClient*>(nc)->sendMove("Test move. C -> S"))
        result=true;

    std::cout << "NTClientSends: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::NTServerSends(NetworkManager *ns)
{
    bool result = false;
    if(dynamic_cast<NetworkServer*>(ns)->sendMove("Test move. S -> C"))
        result=true;

    std::cout << "NTServerSends: " << (result ? "PASSED!" : "failed.") << std::endl;
    return result;
}

bool Tests::NetworkTests()
{
    bool result = false;
    short passed=0, all=0;
    NetworkManager *nc = new NetworkClient();
    NetworkManager *ns = new NetworkServer();
    std::cout << "# Network tests:" << std::endl;
    passed += (NTStartServer(ns, PREFFERED_PORT_NUMBER) ? 1 : 0); all++;
    passed += (NTConnectClient(nc, PREFFERED_PORT_NUMBER) ? 1 : 0); all++;

    QMessageBox::information(NULL, "", "Test srodowiska graficznego.", QMessageBox::Ok);

    passed += (NTClientSends(nc) ? 1 : 0); all++;
    passed += (NTServerSends(ns) ? 1 : 0); all++;
    std::cout << passed << "/" << all << " PASSED!" << std::endl;
    if(passed == all)
        result = true;
    return result;
}


