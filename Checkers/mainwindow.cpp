#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creategamedialog.h"
#include "networkserver.h"
#include "networkclient.h"
#include "move.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionCreateGame, SIGNAL(triggered()), this, SLOT(createGame()));
    connect(ui->actionJoinToGame,SIGNAL(triggered()), this, SLOT(joinToGame()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(aboutWindow()));
    connect(this, SIGNAL(won()), this, SLOT(youWon()));
    connect(this, SIGNAL(lost()), this, SLOT(youLost()));

    setCentralWidget(&view);
    nm = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setScene(QGraphicsScene *board)
{
    view.setScene(board);
    view.show();
}

void MainWindow::aboutWindow()
{
    QMessageBox::about(this, "Checkers", "L.Tomczak & P.Jastrzebski\nZPR 2012\nWEiTI PW");
}

void MainWindow::youLost(){
    QMessageBox::about(this, "Checkers", "Przegrales!");
}

void MainWindow::youWon(){
    QMessageBox::about(this, "Checkers", "Wygrales!");
}

void MainWindow::createGame()
{
    CreateGameDialog createGameDialog("Utworz nowa gre.", this);
    if(createGameDialog.exec() == QDialog::Accepted)
    {
        nm = new NetworkServer();
        dynamic_cast<NetworkServer*>(nm)->startServer(createGameDialog.getServerAddress(), createGameDialog.getServerPort());
        setScene(new Board(this));
        connect(nm, SIGNAL(receivedMove(QString)), this, SLOT(receiveMove(QString)));
        dynamic_cast<Board*>(view.scene())->setGamerColor(Piece::BLACK);
        dynamic_cast<Board*>(view.scene())->blockMoves();
        gs.setIfHereWhite(false);
        ui->pushButton->setStyleSheet("* { background-color: rgb(255,0,0) }");
    }
}

void MainWindow::joinToGame()
{
    CreateGameDialog joinToGameDialog("Dolacz do gry.", this);
    if(joinToGameDialog.exec() == QDialog::Accepted)
    {
        if(nm == NULL)
        {
            nm = new NetworkClient();
            dynamic_cast<NetworkClient*>(nm)->connectTo(joinToGameDialog.getServerAddress(), joinToGameDialog.getServerPort());
            connect(nm, SIGNAL(receivedMove(QString)), this, SLOT(receiveMove(QString)));
            dynamic_cast<Board*>(view.scene())->setGamerColor(Piece::WHITE);
            dynamic_cast<Board*>(view.scene())->blockMoves();
            dynamic_cast<Board*>(view.scene())->unblockMoves();
            gs.setIfHereWhite(true);
            ui->pushButton->setStyleSheet("* { background-color: rgb(255,255,255) }");
        }
        else
            QMessageBox::information(this, "", "Aktualnie utworzyles serwer.", QMessageBox::Ok);
    }
}

bool MainWindow::whitePointsInc(bool ifTest)
{
    int points = gs.getWhitePoints();
    gs.setWhitePoints(++points);
    ui->whitePointsLabel->setText(QString::number(points));
    if(points==PIECE_NUMBER){
        if(!ifTest)
            emit won();
        return true;
    }
    return false;
}

bool MainWindow::blackPointsInc(bool ifTest)
{
    int points = gs.getBlackPoints();
    gs.setBlackPoints(++points);
    ui->blackPointsLabel->setText(QString::number(points));
    if(points==PIECE_NUMBER){
        if(!ifTest)
            emit won();
        return true;
    }
    return false;
}

void MainWindow::sendMove(QString move)
{
    nm->sendMove(move);
}

void MainWindow::receiveMove(QString move)
{
    bool endMove;
    endMove = Move::doMove(move, view.scene());

    if(move.size() == MAX_MOVE_LENGTH || move.size() == MAX_MOVE_LENGTH - 1)
    {
        if(gs.getIfHereWhite()){
            int points = gs.getBlackPoints();
            gs.setBlackPoints(++points);
            ui->blackPointsLabel->setText(QString::number(points));
            if(points==PIECE_NUMBER)
                emit lost();

        }
        else{
            int points = gs.getWhitePoints();
            gs.setWhitePoints(++points);
            ui->whitePointsLabel->setText(QString::number(points));
            if(points==PIECE_NUMBER)
                emit lost();
        }
    }

    if(endMove)
        dynamic_cast<Board*>(view.scene())->unblockMoves();
}
